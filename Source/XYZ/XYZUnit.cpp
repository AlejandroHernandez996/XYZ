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

	if(PushedBy &&
		(!PushedBy->ShouldStatePush() ||
			PushedBy->GetDistanceToLocation2D(GetActorLocation()) > 200.0f))
	{
		PushedBy = nullptr;
		CurrentlyPushing.Empty();
		GetXYZAIController()->XYZStopMovement();
	}
	if (ShouldStatePush())
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
		ScanForBoidMovement();
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
	if(State == EXYZUnitState::IDLE)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;

	}
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
				}else
				{
					GetCharacterMovement()->StopMovementImmediately();
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
				}else
				{
					GetCharacterMovement()->StopMovementImmediately();
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
				}else
				{
					GetCharacterMovement()->StopMovementImmediately();
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
							FVector::Distance(FlyingUnit->GetActorLocation(), GetActorLocation()) < GetCapsuleComponent()->GetScaledCapsuleRadius()*5.0f)
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
					FlyToLocation(GetActorLocation() - WeightedAvgDirection * GetCapsuleComponent()->GetScaledCapsuleRadius()*5.0f, true);
					//SetActorLocation(GetActorLocation() - WeightedAvgDirection * 50.0f * DeltaSeconds);
				}else
				{
					GetCharacterMovement()->StopMovementImmediately();
				}
			}else
			{
				GetCharacterMovement()->StopMovementImmediately();
			}
		}
		break;
	case EXYZUnitState::HOLD:
		GetCharacterMovement()->StopMovementImmediately();
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
				TargetActor = FindClosestActor(false);
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
		//SetActorLocation(NewLocation);
		FlyToLocation(NewLocation);
		SetActorRotation(NewRotation);
	}
}

void AXYZUnit::FlyToLocation(FVector FlyLocation, bool bOverrideRotation)
{
	FVector Direction = (FlyLocation - GetActorLocation()).GetSafeNormal();
	Direction.Z = 0.0f; // Ensure the character stays at the same Z level

	if (GetActorLocation().Z != FlyingZOffset)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation.Z = FlyingZOffset;
		SetActorLocation(CurrentLocation);
	}

	FRotator CurrentRotation = GetActorRotation();

	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	AddMovementInput(Direction);

	if(bOverrideRotation)
	{
		SetActorRotation(CurrentRotation);
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

