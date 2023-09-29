// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZActor.h"
#include "XYZGameState.h"
#include "XYZDecalType.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "XYZAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XYZResourceActor.h"
#include "XYZBuilding.h"
#include "XYZAbility.h"
#include "XYZDeathManager.h"
#include "XYZMapManager.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

// Sets default values
AXYZActor::AXYZActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bReplicates = true;
	if (GetLocalRole() == ROLE_Authority)
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
		InitialCapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
		CurrentCapsuleRadius = InitialCapsuleRadius;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
		AIControllerClass = AXYZAIController::StaticClass();
	}

	Health = 100.0f;
	MaxHealth = 100.0f;
}

void AXYZActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (GetLocalRole() != ROLE_Authority)
	{
		TArray<UDecalComponent*> DecalComponents;
		GetComponents(DecalComponents);
		if (DecalComponents.Num() == 1)
		{
			SelectionDecal = DecalComponents[0];
		}
	}

	int AbilityIndex = 0;
	Abilities.Empty();
	for (TSubclassOf<class UXYZAbility> AbilityTemplate : AbilityTemplates)
	{
		UXYZAbility* Ability = NewObject<UXYZAbility>(this, AbilityTemplate,
		                                              FName(GetName() + "Ability_" + FString::FromInt(AbilityIndex)));
		if (Ability)
		{
			Abilities.Add(Ability);
		}
		AbilityIndex++;
	}
	
}

void AXYZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();
	if(!HasAuthority() && UActorId != -1 && !GameState->ActorsByUID.Contains(UActorId))
	{
		GameState->AddActorClient(this, UActorId);
	}
	if(HasAuthority())
	{
		if(!(State == EXYZUnitState::DEAD || State == EXYZUnitState::HOLD || State == EXYZUnitState::IDLE || State == EXYZUnitState::MINING))
		{
			GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->AddToUpdateSet(this);
		}
	}
}

void AXYZActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZActor, Health);
	DOREPLIFETIME(AXYZActor, MaxHealth);
	DOREPLIFETIME(AXYZActor, MoveSpeed);
	DOREPLIFETIME(AXYZActor, BaseArmor);
	DOREPLIFETIME(AXYZActor, AttackDamage);
	DOREPLIFETIME(AXYZActor, AttackRate);
	DOREPLIFETIME(AXYZActor, AttackRange);
	DOREPLIFETIME(AXYZActor, UActorId);
	DOREPLIFETIME(AXYZActor, State);
	DOREPLIFETIME(AXYZActor, bHasAvoidance);
	DOREPLIFETIME(AXYZActor, CollisionName);
	DOREPLIFETIME(AXYZActor, TeamId);
	DOREPLIFETIME(AXYZActor, ActorId);
}

void AXYZActor::ShowDecal(bool bShowDecal, EXYZDecalType DecalType)
{
	if (!SelectionDecal) return;
	if (!bShowDecal)
	{
		SelectionDecal->SetMaterial(0, DecalMaterials[EXYZDecalType::NEUTRAL]);
	}
	else
	{
		SelectionDecal->SetMaterial(0, DecalMaterials[DecalType]);
	}
}

void AXYZActor::Attack()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	if (TargetActor && !bIsAttackOnCooldown)
	{
		bIsAttackOnCooldown = true;
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this]()
		{
			bIsAttackOnCooldown = false;
		}, AttackRate, false);

		for (AXYZPlayerController* XYZController : GetWorld()->GetAuthGameMode<AXYZGameMode>()->PlayerControllers)
		{
			if (XYZController)
			{
				XYZController->PlayAnimationMontage(EXYZAnimMontageType::ATTACK, this);
			}
		}
		TargetActor->Health = FMath::Clamp(TargetActor->Health - AttackDamage, 0.0f, TargetActor->MaxHealth);
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
		Direction.Z = 0;
		Direction.Normalize();

		FRotator TargetRotation = Direction.Rotation();
		SetActorRotation(TargetRotation);
	}
}

/*
AXYZActor* AXYZActor::FindClosestActor(bool bIgnoreFriendlyActors)
{
	AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();

	AXYZActor* ClosestActor = nullptr;
	float ClosestDistanceSqr = FLT_MAX;
	for (AXYZActor* OtherActor : GameState->GetAllActors())
	{
		bool bTargetIsFriendlyAndShouldIgnore = OtherActor && OtherActor->TeamId == TeamId && bIgnoreFriendlyActors;
		if (!OtherActor || OtherActor == this || bTargetIsFriendlyAndShouldIgnore || OtherActor->Health <= 0.0f ||
			OtherActor->IsA(AXYZResourceActor::StaticClass()))
		{
			continue;
		}

		float DistanceSqr = FVector::DistSquaredXY(this->GetActorLocation(), OtherActor->GetActorLocation());

		if (DistanceSqr < ClosestDistanceSqr && DistanceSqr <= FMath::Square(VisionRange))
		{
			ClosestDistanceSqr = DistanceSqr;
			ClosestActor = OtherActor;
		}
	}

	return ClosestActor;
}
*/

AXYZActor* AXYZActor::FindClosestActor(bool bIgnoreFriendlyActors)
{
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
	TSet<AXYZActor*> ActorsInVision = MapManager->FindActorsInVisionRange(this);
	FVector CurrentLocation = this->GetActorLocation();
	AXYZActor* ClosestActor = nullptr;
	float ClosestDistanceSqr = FLT_MAX;
	for (AXYZActor* OtherActor : ActorsInVision)
	{
		bool bTargetIsFriendlyAndShouldIgnore = OtherActor && OtherActor->TeamId == TeamId && bIgnoreFriendlyActors;
		if (!OtherActor ||
			OtherActor == this ||
			bTargetIsFriendlyAndShouldIgnore ||
			OtherActor->Health <= 0.0f ||
			OtherActor->IsA(AXYZResourceActor::StaticClass()))
		{
			continue;
		}

		float DistanceSqr = FVector::DistSquaredXY(CurrentLocation, OtherActor->GetActorLocation());
		if (DistanceSqr < ClosestDistanceSqr && DistanceSqr <= FMath::Square(VisionRange))
		{
			ClosestDistanceSqr = DistanceSqr;
			ClosestActor = OtherActor;
		}
	}
	
	return ClosestActor;
}

AXYZAIController* AXYZActor::GetXYZAIController()
{
	if (!XYZAIController)
	{
		XYZAIController = GetController<AXYZAIController>();
	}
	return XYZAIController;
}

void AXYZActor::ScanXYZActorsAhead()
{
	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	float Distance = CurrentCapsuleRadius * 2.0f;

	FVector End = ((ForwardVector * Distance) + Start);

	FVector LeftVector = ForwardVector.RotateAngleAxis(-45, FVector(0, 0, 1));
	FVector EndLeft = ((LeftVector * Distance) + Start);

	FVector RightVector = ForwardVector.RotateAngleAxis(45, FVector(0, 0, 1));
	FVector EndRight = ((RightVector * Distance) + Start);

	FVector Left22Vector = ForwardVector.RotateAngleAxis(-22, FVector(0, 0, 1));
	FVector End22Left = ((LeftVector * Distance) + Start);

	FVector Right22Vector = ForwardVector.RotateAngleAxis(22, FVector(0, 0, 1));
	FVector End22Right = ((RightVector * Distance) + Start);

	TSet<AXYZActor*> ActorsFound;
	AXYZActor* ScannedActor = ScanAndPush(Start, EndLeft, ActorsFound);
	if (ScannedActor)
	{
		ActorsFound.Add(ScannedActor);
	}
	ScannedActor = ScanAndPush(Start, EndRight, ActorsFound);
	if (ScannedActor)
	{
		ActorsFound.Add(ScannedActor);
	}
	ScannedActor = ScanAndPush(Start, End22Left, ActorsFound);
	if (ScannedActor)
	{
		ActorsFound.Add(ScannedActor);
	}
	ScannedActor = ScanAndPush(Start, End22Right, ActorsFound);
	if (ScannedActor)
	{
		ActorsFound.Add(ScannedActor);
	}
	ScannedActor = ScanAndPush(Start, End, ActorsFound);
	if (ScannedActor)
	{
		ActorsFound.Add(ScannedActor);
	}
	bHasAvoidance = ActorsFound.IsEmpty();
}

AXYZActor* AXYZActor::ScanAndPush(FVector Start, FVector End, TSet<AXYZActor*> ActorsFound)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams);

	if (!bHit || !HitResult.GetActor()) return nullptr;
	if (!HitResult.GetActor()->IsA(AXYZActor::StaticClass())) return nullptr;
	if (HitResult.GetActor()->IsA(AXYZBuilding::StaticClass())) return nullptr;

	AXYZActor* OtherXYZActor = Cast<AXYZActor>(HitResult.GetActor());

	if (!OtherXYZActor || OtherXYZActor == TargetActor) return nullptr;
	if (!ActorsFound.Contains(OtherXYZActor) && OtherXYZActor->TeamId == TeamId)
	{
		FVector Direction = End - Start;
		Direction.Normalize();
		FVector PushLocation = (Direction * OtherXYZActor->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.0f) +
			OtherXYZActor->GetActorLocation();
		if (OtherXYZActor->State == EXYZUnitState::IDLE)
		{
			if (Direction == GetActorForwardVector())
			{
				PushLocation = (OtherXYZActor->GetActorRightVector() * OtherXYZActor->GetCapsuleComponent()->
					GetScaledCapsuleRadius() * 2.0f) + OtherXYZActor->GetActorLocation();
			}
			OtherXYZActor->GetXYZAIController()->XYZMoveToLocation(PushLocation);
			return OtherXYZActor;
		}
	}
	return nullptr;
}

void AXYZActor::AttackMoveTarget()
{
	AXYZAIController* ActorController = GetXYZAIController();
	FVector ActorLocation = GetActorLocation();
	FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
	if (TargetActor && TargetActor != this && TargetActor->Health > 0.0f)
	{
		FVector TargetActorLocation = TargetActor->GetActorLocation();

		// Assuming TargetActor has a CapsuleComponent named CapsuleComponent.
		float TargetActorRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius();

		FVector Direction = TargetActorLocation - ActorLocation;
		Direction.Z = 0;
		Direction.Normalize();

		FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
		float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

		// Subtract the capsule's radius from the calculated distance.
		DistanceToTarget -= TargetActorRadius;
		if (DistanceToTarget <= AttackRange)
		{
			Attack();
			if (State != EXYZUnitState::HOLD)
			{
				SetState(EXYZUnitState::ATTACKING);
				ActorController->XYZStopMovement();
			}
		}
		else if (State != EXYZUnitState::HOLD)
		{
			ActorController->XYZAttackMoveToTarget(TargetActor);
		}
	}
	else
	{
		TargetActor = nullptr;
	}
}

void AXYZActor::SetState(EXYZUnitState UnitState)
{
	PreviousState = State;
	State = UnitState;
	switch (State)
	{
	case EXYZUnitState::GATHERING:
		break;
	case EXYZUnitState::RETURNING:
		break;
	case EXYZUnitState::IDLE:
		TargetActor = nullptr;
		break;
	case EXYZUnitState::MOVING:
		TargetActor = nullptr;
		break;
	case EXYZUnitState::ATTACK_MOVING:
		break;
	case EXYZUnitState::ATTACKING:
		break;
	case EXYZUnitState::DEAD:
		TargetActor = nullptr;
		break;
	}
}

void AXYZActor::UseAbility(int32 Index)
{
	if (Index >= 0 && Index < Abilities.Num() && Abilities[Index] && !Abilities.IsEmpty())
	{
		Abilities[Index]->Activate();
	}
}

void AXYZActor::PlayAnimationMontage(EXYZAnimMontageType AnimType)
{
	if (AnimMontageMap.Contains(AnimType))
	{
		UAnimMontage* Montage = AnimMontageMap[AnimType];
		if (Montage)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(Montage);
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(
				TimerHandle,
				[this]()
				{
					GetMesh()->GetAnimInstance()->StopAllMontages(.25f);
				},
				Montage->GetPlayLength(),
				false
			);
		}
	}
}

void AXYZActor::Process(float DeltaTime)
{
	if (State == EXYZUnitState::DEAD) return;
	if (Health == 0.0f)
	{
		GetWorld()->GetAuthGameMode<AXYZGameMode>()->DeathManager->QueueDeath(this);
	}
}
