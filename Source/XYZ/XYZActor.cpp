// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZActor.h"
#include "XYZGameState.h"
#include "XYZDecalType.h"
#include "DrawDebugHelpers.h"
#include "NotificationPayload.h"
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
#include "XYZBlob.h"
#include "XYZDeathManager.h"
#include "XYZMapManager.h"
#include "XYZMatchStatsManager.h"
#include "XYZProjectile.h"
#include "XYZProjectileManager.h"
#include "XYZUnitBuff.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AXYZActor::AXYZActor() : Super()
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
	ProjectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnComponent"));
	ProjectileSpawnComponent->SetupAttachment(RootComponent);
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

	AbilitiesTriggeredOnAttack.Empty();
	for (TSubclassOf<class UXYZAbility> AbilityTemplate : AbilitiesTriggeredOnAttackTemplates)
	{
		UXYZAbility* Ability = NewObject<UXYZAbility>(this, AbilityTemplate,
													  FName(GetName() + "_Ability_" + FString::FromInt(AbilityIndex)));
		if (Ability)
		{
			AbilitiesTriggeredOnAttack.Add(Ability);
			Ability->OwningActor = this;
		}
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

	if(HasAuthority() && GetWorld() && GetWorld()->GetAuthGameMode<AXYZGameMode>() && !OwningPlayerController && TeamId >-1 && TeamId < 2)
	{
		for(AXYZPlayerController* PlayerController : GetWorld()->GetAuthGameMode<AXYZGameMode>()->PlayerControllers)
		{
			if(PlayerController && PlayerController->TeamId == TeamId)
			{
					OwningPlayerController = PlayerController;
			}
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
	DOREPLIFETIME(AXYZActor, bHasEverBeenVisibleByEnemy);
	DOREPLIFETIME(AXYZActor, BoidTargetLocation);
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
	if(!TargetActor ||
		TargetActor == this ||
		!TargetActor->CanBeAttacked(this) ||
		TargetActor->State == EXYZUnitState::DEAD)
	{
		TargetActor = nullptr;
		return;
	}
	
	FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
	Direction.Z = 0;
	Direction.Normalize();

	FRotator TargetRotation = Direction.Rotation();
	SetActorRotation(TargetRotation);
	
	if(bIsAttackOnCooldown) return;
	
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
		if(TargetActor->IsA(AXYZBuilding::StaticClass()))
		{
			GetWorld()->GetAuthGameMode<AXYZGameMode>()->MatchStatsManager->AddIntStat(1,EMatchStatType::BUILDINGS_DESTROYED, TeamId);
		}else
		{
			GetWorld()->GetAuthGameMode<AXYZGameMode>()->MatchStatsManager->AddIntStat(1,EMatchStatType::UNITS_KILLED, TeamId);
		}
		
	}
	
	TargetActor->Health = FMath::Clamp(TargetActor->Health + TargetActor->Armor - AttackDamage, 0.0f, TargetActor->MaxHealth);

	if(TeamId != TargetActor->TeamId && TargetActor->TeamId != 2)
	{
		FNotificationPayload NotificationPayload = FNotificationPayload();
		NotificationPayload.NotificationType = TargetActor->IsA(AXYZBuilding::StaticClass()) ?
			ENotificationType::NOTIFY_BUILDINGS_UNDER_ATTACK :
			ENotificationType::NOTIFY_UNITS_UNDER_ATTACK;
		TargetActor->OwningPlayerController->SendNotification(NotificationPayload);
	}

	if(ProjectileTemplate)
	{
		GetWorld()->GetAuthGameMode<AXYZGameMode>()->ProjectileManager->SpawnProjectile(ProjectileTemplate, ProjectileSpawnComponent->GetComponentLocation(), TargetActor,this);
	}
	for(UXYZAbility* Ability : AbilitiesTriggeredOnAttack)
	{
		if(Ability)
		{
			Ability->OwningActor = this;
			Ability->TargetLocation = GetActorLocation();
			Ability->Activate();
		}
	}
}

AXYZActor* AXYZActor::FindClosestActor(bool bIgnoreFriendlyActors)
{
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
	return MapManager->FindClosestEnemyActorInVisionRange(this,bIgnoreFriendlyActors);
}

AXYZAIController* AXYZActor::GetXYZAIController()
{
	if (!XYZAIController)
	{
		XYZAIController = GetController<AXYZAIController>();
	}
	return XYZAIController;
}

void AXYZActor::ScanActorsAndPushWithMapGrid()
{
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
	FVector ForwardDirection = GetCapsuleComponent()->GetForwardVector();
	ForwardDirection.Normalize();
	ForwardDirection.Z = 0.0f;

	TArray<FIntVector2> PerimeterCells = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(1,1)).Array();
	TArray<FIntVector2> PerimeterCells2 = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(2,2)).Array();
	PerimeterCells.Append(PerimeterCells2);
	PerimeterCells.Add(GridCoord);
	
	TSet<AXYZActor*> ActorsFound;

	for (const FIntVector2& GridCell : PerimeterCells)
	{
		if (!MapManager->Grid.Contains(GridCell)) continue;
		TSharedPtr<FGridCell> GridCellData = MapManager->Grid[GridCell];
		for (AXYZActor* ActorInCell : GridCellData->ActorsInCell)
		{
			if (ActorInCell &&
				!ActorInCell->bIsFlying &&
				ActorInCell->IsA(AXYZUnit::StaticClass()) &&
				ActorInCell != this &&
				ActorInCell->TeamId == TeamId &&
				(!ActorInCell->PushedBy || !PushedBy) &&
				ActorInCell->State == EXYZUnitState::IDLE)
			{

				if(TargetActor && TargetActor == ActorInCell) continue;
				if(CurrentBlob && CurrentBlob->AgentsInBlob.Contains(ActorInCell)) continue;
				
				float Distance = FVector2D::Distance(FVector2D(GetActorLocation().X,GetActorLocation().Y), FVector2D(ActorInCell->GetActorLocation().X, ActorInCell->GetActorLocation().Y));
				if(Distance > GetCapsuleComponent()->GetScaledCapsuleRadius() * PushRadiusMultiplier) continue;
				if(GetDistanceToLocation2D(TargetLocation) < Distance) continue;
				FVector DirectionToActor = ActorInCell->GetActorLocation() - GetActorLocation();
				DirectionToActor.Z = 0;
				DirectionToActor.Normalize();
				//OwningPlayerController->DrawLine(GetActorLocation() , GetActorLocation()+DirectionToActor*100.0f, FColor::Red);
				float DotProductValue = FVector::DotProduct(DirectionToActor, ForwardDirection);
				float MaxAngleThreshold = FMath::DegreesToRadians(PushAngle);
				float MinAngleThreshold = -MaxAngleThreshold; 

				if (FMath::Acos(DotProductValue) >= MinAngleThreshold && FMath::Acos(DotProductValue) <= MaxAngleThreshold)
				{
					FVector PushLocation = CalculatePushLocation(ForwardDirection, GridCoord, ActorInCell);
					ActorInCell->GetXYZAIController()->XYZMoveToLocation(PushLocation);
					ActorsFound.Add(ActorInCell);
					ActorInCell->PushedBy = this;
				}
			}
		}
	}
	CurrentlyPushing = ActorsFound;
	bHasAvoidance = ActorsFound.IsEmpty();
}

FVector AXYZActor::CalculatePushLocation(FVector ForwardDirection, FIntVector2 PusherGridCoord, AXYZActor* ActorInCell)
{
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
	float SweepAngleIncrement = 15.0f;
	float MaxSweepAngle = 135.0f;
	float PushDistance = 200.0f;
	
	TSet<FIntVector2> PossiblePushLocations;
	for (float SweepAngle = 45.0f; SweepAngle <= MaxSweepAngle; SweepAngle += SweepAngleIncrement)
	{
		FVector SweepDirection = ForwardDirection.RotateAngleAxis(SweepAngle, FVector::UpVector);
		FVector PushLocation = SweepDirection*PushDistance + GetActorLocation();
		
		//OwningPlayerController->DrawLine(GetActorLocation(), PushLocation,FColor::Green);

		PossiblePushLocations.Add(MapManager->GetGridCoordinate(PushLocation));

		SweepDirection = ForwardDirection.RotateAngleAxis(-SweepAngle, FVector::UpVector);
		PushLocation = SweepDirection*PushDistance + GetActorLocation();
		
		//OwningPlayerController->DrawLine(GetActorLocation(), PushLocation,FColor::Green);
		PossiblePushLocations.Add(MapManager->GetGridCoordinate(PushLocation));
	}

	FIntVector2 BestGridCell;
	float MinDistanceToPusher = MAX_flt;

	for(FIntVector2 PossibleGridLocation : PossiblePushLocations)
	{
		if(!MapManager->IsGridCoordValid(PossibleGridLocation)) continue;

		//if(MapManager->Grid[PossibleGridLocation]->Height != MapManager->Grid[GridCoord]->Height) continue;
		float DistanceToGridCoord = ActorInCell->GetDistanceToLocation2D(MapManager->GridCoordToWorldCoord(PossibleGridLocation));
		if(DistanceToGridCoord < MinDistanceToPusher)
		{
			BestGridCell = PossibleGridLocation;
			MinDistanceToPusher = DistanceToGridCoord;
		}
	}

	if(MinDistanceToPusher == MAX_flt)
	{
		return ActorInCell->GetActorLocation();
	}
	//OwningPlayerController->DrawLine(ActorInCell->GetActorLocation(), MapManager->GridCoordToWorldCoord(BestGridCell),FColor::Blue);
	return MapManager->GridCoordToWorldCoord(BestGridCell);
}

void AXYZActor::AttackMoveTarget()
{
	AXYZAIController* ActorController = GetXYZAIController();
	FVector ActorLocation = GetActorLocation();
	FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);

	if(!TargetActor ||
		TargetActor == this ||
		!TargetActor->CanBeAttacked(this) ||
		TargetActor->State == EXYZUnitState::DEAD)
	{
		TargetActor = nullptr;
		return;
	}
	
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
			ActorController->StopMovement();
		}
	}
	else if (State == EXYZUnitState::HOLD)
	{
		TargetActor = nullptr;
	}else
	{
		ScanForBoidMovement();
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
					if(GetMesh() && GetMesh()->GetAnimInstance())
					{
						GetMesh()->GetAnimInstance()->StopAllMontages(.25f);
					}
				},
				Montage->GetPlayLength(),
				false
			);
		}
	}
	switch (AnimType)
	{
	case EXYZAnimMontageType::ATTACK:
		OnAttackEvent.Broadcast();
		break;
	default: ;
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
	bHasEverBeenVisibleByEnemy = bHasEverBeenVisibleByEnemy || bInEnemyVision;
	bInEnemyTrueVision = MapManager->TeamHasTrueVision(TeamId == 0 ? 1 : 0, GridCoord);

	if(GridCoord != MapManager->GetGridCoordinate(GetActorLocation()) && !this->IsA(AXYZResourceActor::StaticClass()))
	{
		MapManager->AddToUpdateSet(this);
	}

	if(!bIsFlying && (State == EXYZUnitState::MOVING || State == EXYZUnitState::FOLLOWING || State == EXYZUnitState::ATTACKING || State == EXYZUnitState::PLACING || State == EXYZUnitState::ATTACKING))
	{
		bool bWasStuck = bIsStuck;
		bIsStuck = GridCoord == MapManager->GetGridCoordinate(GetActorLocation()) && State == EXYZUnitState::MOVING;

		if(State == EXYZUnitState::FOLLOWING)
		{
			if(TargetActor->bIsFlying)
			{
				GetXYZAIController()->MoveToLocation(MapManager->GridCoordToWorldCoord(TargetActor->GridCoord));
			}else
			{
				GetXYZAIController()->XYZFollowTarget(TargetActor);
			}
		}
		else if(State == EXYZUnitState::MOVING)
		{
			if(!bWasStuck && bIsStuck)
			{
				HardTimeStuck = 0.0f;
				SoftTimeStuck = 0.0f;
			}
			if(bIsStuck)
			{
				HardTimeStuck += DeltaTime;
				SoftTimeStuck += DeltaTime;
				if(SoftTimeStuck >= SoftStuckDuration)
				{
					GetXYZAIController()->RecalculateMove();
					SoftTimeStuck = 0.0f;
				}
				if(HardTimeStuck >= HardStuckDuration)
				{
					GetXYZAIController()->XYZStopMovement();
					bIsStuck = false;
					HardTimeStuck = 0.0f;
					SoftTimeStuck = 0.0f;
				}
			}
		}else
		{
			bIsStuck = false;
			HardTimeStuck = 0.0f;
			SoftTimeStuck = 0.0f;
		}
		}
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

int AXYZActor::GetActorPriority()
{
	if (IsA(AXYZUnit::StaticClass())) return 1;
	if (IsA(AXYZBuilding::StaticClass())) return 2;
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
	if(ActorAudioComponent)
	{
		ActorAudioComponent->Stop();
		ActorAudioComponent->SetSound(Sound);
		ActorAudioComponent->Play();
	}
}

bool AXYZActor::CanBeAttacked(AXYZActor* AttackingActor)
{
	if(AttackingActor)
	{
		bool bCanAttackActorBasedOnHeight = bIsFlying ? AttackingActor->bCanAttackAir : AttackingActor->bCanAttackGround;
		if(AttackingActor->TeamId == TeamId)
		{
			return bCanAttackActorBasedOnHeight;
		}
		if(bIsCloaked)
		{
			return bInEnemyTrueVision && bCanAttackActorBasedOnHeight;
		}
		return bInEnemyVision && bCanAttackActorBasedOnHeight;
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

FVector2D AXYZActor::GetActorLocation2D()
{
	return FVector2D(GetActorLocation().X, GetActorLocation().Y);
}

float AXYZActor::GetDistanceToLocation2D(FVector WorldLocation)
{
	return FVector2D::Distance(GetActorLocation2D(), FVector2D(WorldLocation.X, WorldLocation.Y));
}

void AXYZActor::ScanForBoidMovement()
{
	TimeSinceLastBoidDraw += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;

	TSet<FIntVector2> PerimeterCells = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(1,1));
	TSet<FIntVector2> PerimeterCells2 = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(2,2));
	PerimeterCells.Add(GridCoord);
	PerimeterCells.Append(PerimeterCells);
	PerimeterCells.Append(PerimeterCells2);

	TSet<AXYZActor*> ActorsFound;
	for (const FIntVector2& GridCell : PerimeterCells)
	{
		if (!MapManager->Grid.Contains(GridCell)) continue;
		TSharedPtr<FGridCell> GridCellData = MapManager->Grid[GridCell];
		float DistanceToTarget = TargetActor ? GetDistanceToLocation2D(TargetActor->GetActorLocation()) : GetDistanceToLocation2D(TargetLocation);
		for (AXYZActor* ActorInCell : GridCellData->ActorsInCell)
		{
			if (ActorInCell &&
				!ActorInCell->bIsFlying &&
				ActorInCell->IsA(AXYZUnit::StaticClass()) &&
				ActorInCell != this &&
				((ActorInCell->State == EXYZUnitState::ATTACKING && ActorInCell->IsInAttackRangeOfUnit()) || ActorInCell->State == EXYZUnitState::HOLD || TeamId != ActorInCell->TeamId) &&
				(TargetActor != ActorInCell || !TargetActor) &&
				DistanceToTarget > GetDistanceToLocation2D(ActorInCell->GetActorLocation()))
			{
				ActorsFound.Add(ActorInCell);
			}
		}
	}
	if(ActorsFound.IsEmpty())
	{
		GetXYZAIController()->RecalculateMove();
		return;
	}

	FVector ForwardDirection = TargetActor ? TargetActor->GetActorLocation() - GetActorLocation() : TargetLocation - GetActorLocation();
	ForwardDirection.Normalize();
	ForwardDirection.Z = 0.0f;
    FVector CurrentLocation = GetActorLocation();

    float SweepAngleIncrement = 60.0f;
    float MaxSweepAngle = 300.0f;
	float SweepAngleOffset = 30.0f;
    float MinDistanceToTarget = FLT_MAX;
    FVector BestDirection = ForwardDirection;
	
    for (float SweepAngle = 0.0f; SweepAngle <= MaxSweepAngle; SweepAngle += SweepAngleIncrement)
    {
    	
        FVector SweepDirection = ForwardDirection.RotateAngleAxis(SweepAngle, FVector::UpVector);
    	SweepDirection.Normalize();
    	SweepDirection.Z = 0.0f;
        bool IsBlocked = false;
    	float MaxAngleThreshold = FMath::DegreesToRadians(SweepAngleOffset);
    	float MinAngleThreshold = -MaxAngleThreshold;

    	if(bIsInBoidMovement)
    	{
    		float DotProductValue = FVector::DotProduct(SweepDirection, LastBoidDirection);
    		float MaxAngleThresholdLastBoid = FMath::DegreesToRadians(90.0f);
    		float MinAngleThresholdLastBoid = -MaxAngleThreshold;
    		
    		if (!(FMath::Acos(DotProductValue) >= MinAngleThresholdLastBoid && FMath::Acos(DotProductValue) <= MaxAngleThresholdLastBoid))
    		{
    			continue;
    		}
    	}
    	
        for (AXYZActor* Actor : ActorsFound)
        {
        	FVector ToOther = Actor->GetActorLocation() - CurrentLocation;
        	ToOther.Z = 0.0f;
        	ToOther.Normalize();

        	float DotProductValue = FVector::DotProduct(ToOther, SweepDirection);

        	if (FMath::Acos(DotProductValue) >= MinAngleThreshold && FMath::Acos(DotProductValue) <= MaxAngleThreshold)
        	{
        		IsBlocked = true;
        		break;
        	}
        }
    	
    	if(SweepAngle == 0.0f && !IsBlocked)
    	{
    		GetXYZAIController()->RecalculateMove();
    		if(TimeSinceLastBoidDraw >= DrawBoidThreshold)
    		{
    			//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation()+SweepDirection*200.0f, FColor::Yellow);
    		}
    		return;
    	}

    	if(TimeSinceLastBoidDraw >= DrawBoidThreshold)
    	{
    		//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation()+SweepDirection*25.0f, IsBlocked ? FColor::Red : FColor::Green);
    	}

        if (!IsBlocked)
        {
            float DistanceToTarget =
            	TargetActor
        		? FVector::Dist(CurrentLocation + SweepDirection * GetCapsuleComponent()->GetScaledCapsuleRadius()*2.0f, TargetActor->GetActorLocation())
        		: FVector::Dist(CurrentLocation + SweepDirection * GetCapsuleComponent()->GetScaledCapsuleRadius()*2.0f, TargetLocation);
            if (DistanceToTarget < MinDistanceToTarget)
            {
                MinDistanceToTarget = DistanceToTarget;
                BestDirection = SweepDirection;
            }
        }
    }

    BestDirection.Normalize();
    BoidTargetLocation = CurrentLocation + BestDirection * GetCapsuleComponent()->GetScaledCapsuleRadius()*2.0f;
	bIsInBoidMovement = true;
	LastBoidDirection = BestDirection;
    GetXYZAIController()->MoveToLocation(BoidTargetLocation);

	if(TimeSinceLastBoidDraw >= DrawBoidThreshold)
	{
		//OwningPlayerController->DrawLine(GetActorLocation(), BoidTargetLocation, FColor::Blue);
		TimeSinceLastBoidDraw = 0.0f;
	}
}

bool AXYZActor::ShouldAvoidActor(AXYZActor* OtherActor)
{
	if(!TargetActor) return false;
	if(TargetActor == OtherActor) return false;
	if(TargetActor->TeamId != TeamId) return true;

	switch (TargetActor->State)
	{
	case EXYZUnitState::IDLE:
	case EXYZUnitState::MOVING:
	case EXYZUnitState::DEAD:
	case EXYZUnitState::ATTACK_MOVING:
	case EXYZUnitState::FOLLOWING:
	case EXYZUnitState::RETURNING:
	case EXYZUnitState::MINING:
	case EXYZUnitState::GATHERING:
	case EXYZUnitState::PLACING:
	case EXYZUnitState::BUILDING:
		return false;
	case EXYZUnitState::ATTACKING:
	case EXYZUnitState::HOLD:
		return true;
	default: return false;
	}
}

bool AXYZActor::IsInAttackRangeOfUnit()
{
	if (TargetActor &&
		TargetActor != this &&
		TargetActor->State != EXYZUnitState::DEAD &&
		TargetActor->CanBeAttacked(this))
	{
		FVector ActorLocation = GetActorLocation();
		FVector TargetActorLocation = TargetActor->GetActorLocation();
		float TargetActorRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius();
		FVector Direction = TargetActorLocation - ActorLocation;
		Direction.Z = 0;
		Direction.Normalize();

		float DistanceToTarget = GetDistanceToLocation2D(TargetActorLocation);

		DistanceToTarget -= TargetActorRadius;
		return DistanceToTarget <= AttackRange;
	}
	return false;
}