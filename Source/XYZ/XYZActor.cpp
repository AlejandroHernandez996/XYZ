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
#include "XYZProjectile.h"
#include "XYZProjectileManager.h"
#include "XYZUnitBuff.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/AudioComponent.h"

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
	FName AudioComponentName = FName(*(GetName() + "_AudioComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(AudioComponentName);
	ProjectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnComponent"));
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
		                                              FName(GetName() + "_Ability_" + FString::FromInt(AbilityIndex)));
		if (Ability)
		{
			Abilities.Add(Ability);
			Ability->OwningActor = this;
		}
		AbilityIndex++;
	}
	LastLocation = GetActorLocation();
}

void AXYZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FloatingMesh && !HasAuthority()) {
		float Time = GetWorld()->GetTimeSeconds();
		FVector NewLocation = FloatingMesh->GetRelativeLocation();

		NewLocation.Z += FMath::Sin(Time * FloatSpeed) * FloatAmplitude * DeltaTime;
		FloatingMesh->SetRelativeLocation(NewLocation);
	}
	AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();
	if(!HasAuthority() && UActorId != -1 && !GameState->ActorsByUID.Contains(UActorId))
	{
		GameState->AddActorClient(this, UActorId);
	}
	if (!HasAuthority() && !bSetTeamColor && (TeamId == 0 || TeamId == 1))
	{
		SetTeamColor();
		
		bSetTeamColor = true; 
	}
	if(HasAuthority())
	{
		if(TargetActor)
		{
			TargetActorLocationReplicated = TargetActor->GetActorLocation();
		}else
		{
			TargetActorLocationReplicated = FVector::ZeroVector;
		}
	}
}

void AXYZActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZActor, Health);
	DOREPLIFETIME(AXYZActor, MaxHealth);
	DOREPLIFETIME(AXYZActor, Energy);
	DOREPLIFETIME(AXYZActor, MaxEnergy);
	DOREPLIFETIME(AXYZActor, Armor);
	DOREPLIFETIME(AXYZActor, MoveSpeed);
	DOREPLIFETIME(AXYZActor, BaseArmor);
	DOREPLIFETIME(AXYZActor, AttackDamage);
	DOREPLIFETIME(AXYZActor, AttackRate);
	DOREPLIFETIME(AXYZActor, AttackRange);
	DOREPLIFETIME(AXYZActor, CastRange);
	DOREPLIFETIME(AXYZActor, UActorId);
	DOREPLIFETIME(AXYZActor, State);
	DOREPLIFETIME(AXYZActor, bHasAvoidance);
	DOREPLIFETIME(AXYZActor, CollisionName);
	DOREPLIFETIME(AXYZActor, TeamId);
	DOREPLIFETIME(AXYZActor, ActorId);
	DOREPLIFETIME(AXYZActor, TargetActorLocationReplicated);
	DOREPLIFETIME(AXYZActor, TotalKills);
	DOREPLIFETIME(AXYZActor, ActiveBuffIds);
	DOREPLIFETIME(AXYZActor, FlyingSpeed);
	DOREPLIFETIME(AXYZActor, CurrentAvoidanceWeight);
	DOREPLIFETIME(AXYZActor, PathingPoints);
	DOREPLIFETIME(AXYZActor, PathingPointsShowFlag);
	DOREPLIFETIME(AXYZActor, PathingPointsColors);
	DOREPLIFETIME(AXYZActor, bHasTrueVision);
	DOREPLIFETIME(AXYZActor, bIsCloaked);
	DOREPLIFETIME(AXYZActor, bInEnemyVision);
	DOREPLIFETIME(AXYZActor, bInEnemyTrueVision);
}

void AXYZActor::ShowDecal(bool bShowDecal, EXYZDecalType DecalType)
{
	if (!SelectionDecal) return;

	for(UStaticMeshComponent* LineComponent : LineMeshes)
	{
		if(!bShowDecal)
		{
			LineComponent->SetMaterial(0, LineMaterials[EXYZDecalType::NEUTRAL]);
		}else
		{
			LineComponent->SetMaterial(0, LineMaterials[DecalType]);
		}
	}
	if (!bShowDecal)
	{
		SelectionDecal->SetMaterial(0, DecalMaterials[EXYZDecalType::NEUTRAL]);
		CurrentDecal = EXYZDecalType::NEUTRAL;
	}
	else
	{
		SelectionDecal->SetMaterial(0, DecalMaterials[DecalType]);
		CurrentDecal = DecalType;
	}
}

void AXYZActor::Attack()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	if(TargetActor && !TargetActor->CanAttack(this))
	{
		TargetActor = nullptr;
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
		if(TargetActor->Health > 0.0f && TargetActor->Health + TargetActor->Armor - AttackDamage <= 0.0f)
		{
			TotalKills++;
		}
		
		TargetActor->Health = FMath::Clamp(TargetActor->Health + TargetActor->Armor - AttackDamage, 0.0f, TargetActor->MaxHealth);
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
		Direction.Z = 0;
		Direction.Normalize();

		FRotator TargetRotation = Direction.Rotation();
		SetActorRotation(TargetRotation);

		if(ProjectileTemplate)
		{
			GetWorld()->GetAuthGameMode<AXYZGameMode>()->ProjectileManager->SpawnProjectile(ProjectileTemplate, ProjectileSpawnComponent->GetComponentLocation(), TargetActor,this);
		}
	}
}

AXYZActor* AXYZActor::FindClosestActor(bool bIgnoreFriendlyActors)
{
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
	TSet<AXYZActor*> ActorsInVision = MapManager->FindActorsInVisionRange(this);
	FVector CurrentLocation = this->GetActorLocation();
	
	AXYZActor* ClosestActor = nullptr;
	float ClosestDistanceSqr = FLT_MAX;
	int ClosestActorPriority = INT_MAX;

	for (AXYZActor* OtherActor : ActorsInVision)
	{
		bool bTargetIsFriendlyAndShouldIgnore = OtherActor && OtherActor->TeamId == TeamId && bIgnoreFriendlyActors;
		if (!OtherActor ||
			OtherActor == this ||
			bTargetIsFriendlyAndShouldIgnore ||
			OtherActor->State == EXYZUnitState::DEAD ||
			OtherActor->IsA(AXYZResourceActor::StaticClass()) ||
			!OtherActor->CanAttack(this))
		{
			continue;
		}

		float DistanceSqr = FVector::DistSquaredXY(CurrentLocation, OtherActor->GetActorLocation());
		int ActorPriority = GetActorPriority(OtherActor);

		bool bIsCloser = DistanceSqr < ClosestDistanceSqr && DistanceSqr <= FMath::Square(VisionRange);
		bool bHasHigherPriority = (DistanceSqr == ClosestDistanceSqr) && (ActorPriority < ClosestActorPriority);

		if (bIsCloser || bHasHigherPriority)
		{
			ClosestDistanceSqr = DistanceSqr;
			ClosestActor = OtherActor;
			ClosestActorPriority = ActorPriority;
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
	FVector End22Left = ((Left22Vector * Distance) + Start);

	FVector Right22Vector = ForwardVector.RotateAngleAxis(22, FVector(0, 0, 1));
	FVector End22Right = ((Right22Vector * Distance) + Start);

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
	if(TargetActor && !TargetActor->CanAttack(this))
	{
		TargetActor = nullptr;
		return;
	}
	if (TargetActor &&
		TargetActor != this &&
		TargetActor->State != EXYZUnitState::DEAD )
	{
		FVector TargetActorLocation = TargetActor->GetActorLocation();
		
		float TargetActorRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius();

		FVector Direction = TargetActorLocation - ActorLocation;
		Direction.Z = 0;
		Direction.Normalize();

		FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
		float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);
		
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
		}else
		{
			TargetActor = nullptr;
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
		bool bIsActivated = Abilities[Index]->Activate();
		if(bIsActivated && Abilities[Index]->AbilitySoundEffect)
		{
			for(AXYZPlayerController* PlayerController : GetWorld()->GetAuthGameMode<AXYZGameMode>()->PlayerControllers)
			{
				PlayerController->PlayAbilitySound(UActorId, Index);
			}
		}
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
	if (Health <= 0.0f)
	{
		GetWorld()->GetAuthGameMode<AXYZGameMode>()->DeathManager->QueueDeath(this);
		return;
	}
	if(MaxEnergy > 0 && Energy < MaxEnergy)
	{
		Energy += FMath::Clamp(DeltaTime*EnergyRecoveryRatePerSecond,0.0f,MaxEnergy);
	}
	for(UXYZUnitBuff* Buff : ActiveBuffs)
	{
		Buff->Process(DeltaTime);
	}
	for(UXYZUnitBuff* Buff : BuffsToRemove)
	{
		RemoveBuff(Buff);
	}
	BuffsToRemove.Empty();
	
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;

	bInEnemyVision = MapManager->TeamHasVision(TeamId == 0 ? 1 : 0, GridCoord);
	bInEnemyTrueVision = MapManager->TeamHasTrueVision(TeamId == 0 ? 1 : 0, GridCoord);
	MapManager->AddToUpdateSet(this);
	LastLocation = GetActorLocation();
}

void AXYZActor::SetTeamColor()
{
	if (TeamColors.IsValidIndex(TeamId))
	{
		UMaterialInstance* DesiredMaterial = TeamColors[TeamId];

		TArray<UActorComponent*> StaticMeshComponents = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("TeamColor"));
		TArray<UActorComponent*> SkeletalMeshComponents = GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName("TeamColor"));
		StaticMeshComponents.Append(SkeletalMeshComponents);

		for (UActorComponent* Component : StaticMeshComponents)
		{
			if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Component))
			{
				MeshComp->SetMaterial(0, DesiredMaterial);
			}
			else if (USkeletalMeshComponent* SkelMeshComp = Cast<USkeletalMeshComponent>(Component))
			{
				SkelMeshComp->SetMaterial(0, DesiredMaterial);
			}
		}
	}
}

int AXYZActor::GetActorPriority(const AXYZActor* Actor)
{
	if (Actor->IsA(AXYZUnit::StaticClass())) return 1;
	if (Actor->IsA(AXYZBuilding::StaticClass())) return 2;
	return 3;
}

void AXYZActor::RemoveBuff(UXYZUnitBuff* Buff)
{
	if(!Buff) return;

	Buff->DebuffActor(this);
	ActiveBuffs.Remove(Buff);
	ActiveBuffIds.Remove(Buff->BuffId);
}

void AXYZActor::AddBuff(UXYZUnitBuff* Buff)
{
	if(!Buff) return;

	UXYZUnitBuff* FoundUnitBuff = nullptr;
	for(UXYZUnitBuff* UnitBuff : ActiveBuffs)
	{
		if(UnitBuff->BuffId == Buff->BuffId)
		{
			FoundUnitBuff = UnitBuff;
			break;
		}
	}
	if(FoundUnitBuff)
	{
		RemoveBuff(FoundUnitBuff);
	}
	ActiveBuffs.Add(Buff);
	ActiveBuffIds.Add(Buff->BuffId);
	
	
}

void AXYZActor::PlaySound(USoundBase* Sound)
{
	if(AudioComponent)
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(Sound);
		AudioComponent->Play();
	}
}

bool AXYZActor::CanAttack(AXYZActor* AttackingActor)
{
	if(AttackingActor)
	{
		bool bCanAttackActorBasedOnHeight = bIsFlying ? AttackingActor->bCanAttackAir : AttackingActor->bCanAttackGround;
		bool bCanAttackCloakedActor = !bIsCloaked || bInEnemyTrueVision;
		return bCanAttackActorBasedOnHeight && (bCanAttackCloakedActor || TeamId == AttackingActor->TeamId);
	}
	return false;
}

bool AXYZActor::CanUseAbility()
{
	return State != EXYZUnitState::DEAD;
}

void AXYZActor::SetIsCloaked(bool bIsActorCloaked)
{
	bIsCloaked = bIsActorCloaked;
	for(AXYZPlayerController* PlayerController : GetWorld()->GetAuthGameMode<AXYZGameMode>()->PlayerControllers)
	{
		if(bIsCloaked)
		{
			PlayerController->CloakActor(this);
		}else
		{
			PlayerController->UncloakActor(this);
		}
	}
}
