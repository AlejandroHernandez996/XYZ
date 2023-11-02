// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUnit.h"

#include "XYZAIController.h"
#include "XYZBuilding.h"
#include "XYZGameMode.h"
#include "XYZWorker.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XYZMapManager.h"

void AXYZUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!HasAuthority())
	{
		UpdateCollision();
	}
}

void AXYZUnit::Process(float DeltaTime)
{
	Super::Process(DeltaTime);
	if (State == EXYZUnitState::DEAD) return;
	
	UpdateCollision();
	if (bIsFlying) {
		ProcessFlyingUnit(DeltaTime);
		return;
	}

	if(State == EXYZUnitState::MOVING && PushedBy && PushedBy->State != EXYZUnitState::MOVING)
	{
		PushedBy = nullptr;
		CurrentlyPushing.Empty();
		GetXYZAIController()->XYZStopMovement();
	}
	if (State == EXYZUnitState::MOVING || State == EXYZUnitState::ATTACK_MOVING || State == EXYZUnitState::FOLLOWING)
	{
		if(TimeSinceScanForPush == 0.0)
		{
			ScanActorsAndPushWithMapGrid();
		}
		TimeSinceScanForPush += DeltaTime;
		if(TimeSinceScanForPush >= ScanForPushRate)
		{
			TimeSinceScanForPush = 0.0f;
		}
	}
	
	if (State == EXYZUnitState::ATTACK_MOVING ||
		(State == EXYZUnitState::IDLE && !this->IsA(AXYZWorker::StaticClass())) ||
		State == EXYZUnitState::ATTACKING ||
		State == EXYZUnitState::HOLD)
	{
		// If Target is not in vision go idle
		if(TargetActor && !TargetActor->bInEnemyVision && TeamId != TargetActor->TeamId)
		{
			if(State != EXYZUnitState::HOLD)
			{
				GetXYZAIController()->XYZStopMovement();
			}
			TargetActor = nullptr;
		}

		// If no target or target is dead find closest actor
		if (!TargetActor || TargetActor->State == EXYZUnitState::DEAD)
		{
			if(TimeSinceScanForTarget == 0.0)
			{
				TargetActor = FindClosestActor(true);
				if(TargetActor)
				{
					TargetLocation = TargetActor->GetActorLocation();
				}
			}
			TimeSinceScanForTarget += DeltaTime;
			if(TimeSinceScanForTarget >= ScanForTargetRate)
			{
				TimeSinceScanForTarget = 0.0f;
			}
		}

		// if we have a target
		if (TargetActor)
		{
			AttackMoveTarget();
		}

		// if we still dont have a target and we were attacking attack move to our target location
		if (!TargetActor && State == EXYZUnitState::ATTACKING)
		{
			GetXYZAIController()->XYZAttackMoveToLocation(TargetLocation);
		}
	}
	
	if (State == EXYZUnitState::FOLLOWING)
	{
		if (!TargetActor || TargetActor->State == EXYZUnitState::DEAD)
		{
			GetXYZAIController()->XYZStopMovement();
		}
	}
}

void AXYZUnit::ProcessFlyingUnit(float DeltaSeconds)
{
	FVector CurrentLocation = GetActorLocation();
	TargetLocation.Z = CurrentLocation.Z;
	FVector NewLocation;
	bool bUpdateLocation = false;
	FVector DirectionToTarget;
	FVector TargetActorLocation;
	FVector DirectionToAttackLocation;
	FRotator NewRotation;
	float DistanceToTargetActor = 0.0f;
	if(TargetActor)
	{
		DistanceToTargetActor = FVector2D::Distance(FVector2D(TargetActor->GetActorLocation().X, TargetActor->GetActorLocation().Y), FVector2D(GetActorLocation().X, GetActorLocation().Y));
	}
	float DistanceToTargetLocation = FVector2D::Distance(FVector2D(TargetLocation.X, TargetLocation.Y), FVector2D(GetActorLocation().X, GetActorLocation().Y));
	bool bHasReachedTargetLocation = DistanceToTargetLocation < 10.0f;
	switch (State) {
	case EXYZUnitState::MOVING:
		if(bHasReachedTargetLocation)
		{
			GetXYZAIController()->XYZStopMovement();
		}else
		{
			DirectionToTarget = (TargetLocation - CurrentLocation).GetSafeNormal();
			NewLocation = CurrentLocation + DirectionToTarget * FlyingSpeed * DeltaSeconds;
			NewRotation = (TargetLocation - NewLocation).Rotation();
			bUpdateLocation = true;
		}
		break;
	case EXYZUnitState::ATTACK_MOVING:
	case EXYZUnitState::ATTACKING:
		if(TargetActor)
		{
			if(!GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->DoesActorHasVisionOfActor(this, TargetActor))
			{
				TargetActor = nullptr;
			}else
			{
				FlyingAttackMoveTarget();
				if(!IsInAttackRangeOfUnit() && TargetActor)
				{
					TargetActorLocation = TargetActor->GetActorLocation();
					TargetActorLocation.Z = CurrentLocation.Z;
					DirectionToAttackLocation = (TargetActorLocation - CurrentLocation).GetSafeNormal();
					NewLocation = CurrentLocation + DirectionToAttackLocation * FlyingSpeed * DeltaSeconds;
					NewRotation = (TargetActorLocation - NewLocation).Rotation();
					bUpdateLocation = true;
				}
			}
		}else
		{
			if(!bIsPassive)
			{
				if(TimeSinceScanForTarget == 0.0f)
				{
					TargetActor = FindClosestActor(true);
				}
				TimeSinceScanForTarget += DeltaSeconds;
				if(TimeSinceScanForTarget >= ScanForTargetRate)
				{
					TimeSinceScanForTarget = 0.0f;
				}

			}
			DirectionToAttackLocation = (TargetLocation - CurrentLocation).GetSafeNormal();
			NewLocation = CurrentLocation + DirectionToAttackLocation * FlyingSpeed * DeltaSeconds;
			NewRotation = (TargetLocation - NewLocation).Rotation();
			bUpdateLocation = true;
		}
		if(!TargetActor && bHasReachedTargetLocation)
		{
			GetXYZAIController()->XYZStopMovement();
			break;
		}
		break;
	case EXYZUnitState::FOLLOWING:
		if(TargetActor)
		{
			if(TargetActor->bIsFlying)
			{
				if(DistanceToTargetActor > GetCapsuleComponent()->GetScaledCapsuleRadius()*2.0f)
				{
					TargetActorLocation = TargetActor->GetActorLocation();
					TargetActorLocation.Z = CurrentLocation.Z;
					DirectionToAttackLocation = (TargetActorLocation - CurrentLocation).GetSafeNormal();
					NewLocation = CurrentLocation + DirectionToAttackLocation * FlyingSpeed * DeltaSeconds;
					NewRotation = (TargetActorLocation - NewLocation).Rotation();
					bUpdateLocation = true;
				}
			}else
			{
				if(DistanceToTargetActor > GetCapsuleComponent()->GetScaledCapsuleRadius())
				{
					TargetActorLocation = TargetActor->GetActorLocation();
					TargetActorLocation.Z = CurrentLocation.Z;
					DirectionToAttackLocation = (TargetActorLocation - CurrentLocation).GetSafeNormal();
					NewLocation = CurrentLocation + DirectionToAttackLocation * FlyingSpeed * DeltaSeconds;
					NewRotation = (TargetActorLocation - NewLocation).Rotation();
					bUpdateLocation = true;
				}else if(TargetActor->IsA(AXYZBuilding::StaticClass()))
				{
					SetState(EXYZUnitState::IDLE);
				}
			}
		}else
		{
			GetXYZAIController()->XYZStopMovement();
		}
		break;
	case EXYZUnitState::IDLE:
		if(!bIsPassive)
		{
			if(TimeSinceScanForTarget == 0.0f)
			{
				TargetActor = FindClosestActor(true);
			}
			TimeSinceScanForTarget += DeltaSeconds;
			if(TimeSinceScanForTarget >= ScanForTargetRate)
			{
				TimeSinceScanForTarget = 0.0f;
			}
			
		}
		if(TargetActor)
		{
			GetXYZAIController()->XYZAttackMoveToTarget(TargetActor);
		}else
		{
			UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;

			if (MapManager->Grid.Contains(GridCoord) && MapManager->Grid[GridCoord]->ActorsInCell.Contains(this))
			{
				TArray<FVector> OtherFlyingUnitLocations;
				TSet<FIntVector2> UnitAreaCoords = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(2,2));
				UnitAreaCoords = UnitAreaCoords.Union(MapManager->GetPerimeterCoords(GridCoord, FIntVector2(1,1)));

				UnitAreaCoords.Add(GridCoord);

				for(FIntVector2 AreaCoord : UnitAreaCoords)
				{
					if(!MapManager->Grid.Contains(AreaCoord)) continue;
					TSet<AXYZActor*> FlyingUnitsInCoord = MapManager->Grid[AreaCoord]->ActorsInCell;
					for (AXYZActor* FlyingUnit : FlyingUnitsInCoord)
					{
						if (!FlyingUnit) continue;
						if (FlyingUnit->bIsFlying &&
							FlyingUnit->State == EXYZUnitState::IDLE &&
							FlyingUnit->TeamId == TeamId &&
							FlyingUnit != this &&
							FVector::Distance(FlyingUnit->GetActorLocation(), GetActorLocation()) < GetCapsuleComponent()->GetScaledCapsuleRadius()*3.0f)
						{
							OtherFlyingUnitLocations.Add(FlyingUnit->GetActorLocation());
						}
					}
				}
				if (OtherFlyingUnitLocations.Num() > 0)
				{
					FVector WeightedAvgDirection = FVector::ZeroVector;
					float TotalWeight = 0.0f;

					for (const FVector& Location : OtherFlyingUnitLocations)
					{
						float Weight = 1.0f / FMath::Max(1.0f, FVector::Dist(Location, GetActorLocation()));
						WeightedAvgDirection += Weight * (Location - GetActorLocation());
						TotalWeight += Weight;
					}

					if (TotalWeight > 0.0f)
					{
						WeightedAvgDirection /= TotalWeight;
						WeightedAvgDirection.Normalize();
					}
					SetActorLocation(GetActorLocation() - WeightedAvgDirection * 50.0f * DeltaSeconds);
				}
			}
		}
		break;
	case EXYZUnitState::HOLD:
		if(bIsPassive)
		{
			SetState(EXYZUnitState::IDLE);
			break;
		}
		if(TargetActor)
		{
			if(!GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->DoesActorHasVisionOfActor(this, TargetActor))
			{
				TargetActor = nullptr;
			}else
			{
				FlyingAttackMoveTarget();
			}
		}else
		{
			if(TimeSinceScanForTarget == 0.0f)
			{
				TargetActor = FindClosestActor(true);
			}
			TimeSinceScanForTarget += DeltaSeconds;
			if(TimeSinceScanForTarget >= ScanForTargetRate)
			{
				TimeSinceScanForTarget = 0.0f;
			}
		}
		break;
	default:;
	}

	if(bUpdateLocation)
	{
		NewLocation.Z = FlyingZOffset;
		SetActorLocation(NewLocation);
		SetActorRotation(NewRotation);
	}
}

void AXYZUnit::UpdateCollision()
{
	if(HasAuthority() && CurrentCapsuleRadius != GetCapsuleComponent()->GetScaledCapsuleRadius())
	{
		GetCapsuleComponent()->SetCapsuleRadius(CurrentCapsuleRadius);
	}
	if(GetCharacterMovement()->AvoidanceConsiderationRadius != CurrentCapsuleRadius * 2.0f)
	{
		GetCharacterMovement()->AvoidanceConsiderationRadius = CurrentCapsuleRadius * 2.0f;
	}
	if(GetCharacterMovement()->bUseRVOAvoidance != bHasAvoidance)
	{
		GetCharacterMovement()->bUseRVOAvoidance = bHasAvoidance;
	}
	if(GetCharacterMovement()->AvoidanceWeight != CurrentAvoidanceWeight)
	{
		GetCharacterMovement()->AvoidanceWeight = CurrentAvoidanceWeight;
	}
	if(GetCapsuleComponent()->GetCollisionProfileName() != CollisionName)
	{
		GetCapsuleComponent()->SetCollisionProfileName(CollisionName);
	}
}

void AXYZUnit::FlyingAttackMoveTarget()
{
	if(TargetActor && !TargetActor->CanBeAttacked(this))
	{
		if(TargetActor->bIsCloaked)
		{
			GetXYZAIController()->XYZStopMovement();
		}
		TargetActor = nullptr;
		return;
	}
	if(TargetActor->State == EXYZUnitState::DEAD)
	{
		TargetActor = nullptr;
		return;
	}
	if(IsInAttackRangeOfUnit())
	{
		Attack();
	}else if(State == EXYZUnitState::HOLD)
	{
		TargetActor = nullptr;
	}
}

bool AXYZUnit::IsInAttackRangeOfUnit()
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