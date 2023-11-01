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
	if(TargetActor && !TargetActor->CanBeAttacked(this))
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
			if(TargetActor->IsA(AXYZBuilding::StaticClass()))
			{
				TSharedPtr<FMatchStatPayload> BuildingsDestroyedStat = MakeShared<FMatchStatPayload>(FMatchStatPayload());
				BuildingsDestroyedStat->TeamId = TeamId;
				BuildingsDestroyedStat->IntValue = 1;
				BuildingsDestroyedStat->StatType = EMatchStatType::BUILDINGS_DESTROYED;
				GetWorld()->GetAuthGameMode<AXYZGameMode>()->MatchStatsManager->AddIntStat(BuildingsDestroyedStat);
			}else
			{
				TSharedPtr<FMatchStatPayload> UnitsKilledStat = MakeShared<FMatchStatPayload>(FMatchStatPayload());
				UnitsKilledStat->TeamId = TeamId;
				UnitsKilledStat->IntValue = 1;
				UnitsKilledStat->StatType = EMatchStatType::UNITS_KILLED;
				GetWorld()->GetAuthGameMode<AXYZGameMode>()->MatchStatsManager->AddIntStat(UnitsKilledStat);
			}
			
		}
		
		TargetActor->Health = FMath::Clamp(TargetActor->Health + TargetActor->Armor - AttackDamage, 0.0f, TargetActor->MaxHealth);
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
		Direction.Z = 0;
		Direction.Normalize();

		FRotator TargetRotation = Direction.Rotation();
		SetActorRotation(TargetRotation);

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
	//OwningPlayerController->DrawLine(GetActorLocation() , GetActorLocation()+ForwardDirection*1000.0f, FColor::Blue);

	//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation() + ShiftedDirectionMin * 100.0f, FColor::White);
	//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation() + ShiftedDirectionMax * 100.0f, FColor::Yellow);
	//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation() + ForwardDirection.RotateAngleAxis(PushAngleInside,FVector(0,0,1)) * 100.0f, FColor::Blue);
	//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation() + ForwardDirection.RotateAngleAxis(-PushAngleInside,FVector(0,0,1)) * 100.0f, FColor::Blue);
	//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation() + ForwardDirection.RotateAngleAxis(PushAngleOutside,FVector(0,0,1)) * 100.0f, FColor::Yellow);
	//OwningPlayerController->DrawLine(GetActorLocation(), GetActorLocation() + ForwardDirection.RotateAngleAxis(-PushAngleOutside,FVector(0,0,1)) * 100.0f, FColor::Yellow);
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
				ActorInCell->PushedBy == nullptr &&
				(ActorInCell->State == EXYZUnitState::IDLE || (ActorInCell->PushedBy && !PushedBy)))
			{

				if(TargetActor && TargetActor == ActorInCell) continue;
				if(CurrentBlob && CurrentBlob->AgentsInBlob.Contains(ActorInCell)) continue;
				
				float Distance = FVector2D::Distance(FVector2D(GetActorLocation().X,GetActorLocation().Y), FVector2D(ActorInCell->GetActorLocation().X, ActorInCell->GetActorLocation().Y));
				if(Distance > GetCapsuleComponent()->GetScaledCapsuleRadius() * PushRadiusMultiplier) continue;
				
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

	TArray<FIntVector2> PerimeterCoords = MapManager->GetPerimeterCoords(ActorInCell->GridCoord, FIntVector2(1, 1)).Array();
	TSet<FIntVector2> CoordsToSkip = { PusherGridCoord, ActorInCell->GridCoord };

	FIntVector2 BestGridCell = PerimeterCoords[0];
	float MinDistanceToPusher = MAX_flt;
	
	for (const FIntVector2& GridCell : PerimeterCoords)
	{
		if (MapManager->Grid.Contains(GridCell) && !CoordsToSkip.Contains(GridCell) && MapManager->Grid[GridCell]->Height == MapManager->Grid[ActorInCell->GridCoord]->Height)
		{
			TSharedPtr<FGridCell> GridCellData = MapManager->Grid[GridCell];
			int32 ActorsInCell = GridCellData->ActorsInCell.Num();
			float Distance = FVector2D::Distance(FVector2D(ActorInCell->GetActorLocation().X, ActorInCell->GetActorLocation().Y), FVector2D(MapManager->GridCoordToWorldCoord(GridCell).X,MapManager->GridCoordToWorldCoord(GridCell).Y));
			FVector DirectionFromActorToCell = MapManager->GridCoordToWorldCoord(GridCell) - GetActorLocation();
			DirectionFromActorToCell.Normalize();
			DirectionFromActorToCell.Z = 0.0f;

			float DotProductValue = FVector::DotProduct(DirectionFromActorToCell.GetSafeNormal(), ForwardDirection);

			float OutsideMaxAngleThreshold = FMath::DegreesToRadians(PushAngleOutside);
			float OutsideMinAngleThreshold = -OutsideMaxAngleThreshold;
			float InsideMaxAngleThreshold = FMath::DegreesToRadians(PushAngleInside);
			float InsideMinAngleThreshold = -InsideMaxAngleThreshold;

			bool bInsideOutsideRange = FMath::Acos(DotProductValue) >= OutsideMinAngleThreshold && FMath::Acos(DotProductValue) <= OutsideMaxAngleThreshold;
			bool bInsideInsideRange = FMath::Acos(DotProductValue) >= InsideMinAngleThreshold && FMath::Acos(DotProductValue) <= InsideMaxAngleThreshold;
			if (bInsideOutsideRange && !bInsideInsideRange && Distance < MinDistanceToPusher)
			{
				//OwningPlayerController->DrawLine(ActorInCell->GetActorLocation(), GetActorLocation()+DirectionFromActorToCell*Distance, FColor::Green);
				MinDistanceToPusher = Distance;
				BestGridCell = GridCell;
				SoftTimeStuck = 0.0f;
				HardTimeStuck = 0.0f;
			}else
			{
				//OwningPlayerController->DrawLine(ActorInCell->GetActorLocation(), GetActorLocation()+DirectionFromActorToCell*Distance, FColor::Red);
			}
		}
	}

	return MapManager->GridCoordToWorldCoord(BestGridCell);
}

void AXYZActor::AttackMoveTarget()
{
	AXYZAIController* ActorController = GetXYZAIController();
	FVector ActorLocation = GetActorLocation();

	FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
	if(TargetActor && !TargetActor->CanBeAttacked(this))
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
	bHasEverBeenVisibleByEnemy = bHasEverBeenVisibleByEnemy || bInEnemyVision;
	bInEnemyTrueVision = MapManager->TeamHasTrueVision(TeamId == 0 ? 1 : 0, GridCoord);

	if(GridCoord != MapManager->GetGridCoordinate(GetActorLocation()) && !this->IsA(AXYZResourceActor::StaticClass()))
	{
		MapManager->AddToUpdateSet(this);
	}

	if(!bIsFlying && (State == EXYZUnitState::MOVING || State == EXYZUnitState::FOLLOWING))
	{
		bool bWasStuck = bIsStuck;
		bIsStuck = GridCoord == MapManager->GetGridCoordinate(GetActorLocation()) && State == EXYZUnitState::MOVING;

		if(State == EXYZUnitState::FOLLOWING)
		{
			GetXYZAIController()->XYZFollowTarget(TargetActor);
		}else if(State == EXYZUnitState::MOVING)
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
	if(AudioComponent)
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(Sound);
		AudioComponent->Play();
	}
}

bool AXYZActor::CanBeAttacked(AXYZActor* AttackingActor)
{
	if(AttackingActor)
	{
		bool bCanAttackActorBasedOnHeight = bIsFlying ? AttackingActor->bCanAttackAir : AttackingActor->bCanAttackGround;
		bool bCanAttackCloakedActor = !bIsCloaked || bInEnemyTrueVision;
		return bInEnemyVision && bCanAttackActorBasedOnHeight && (bCanAttackCloakedActor || TeamId == AttackingActor->TeamId);
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
