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
}

void AXYZUnit::Process(float DeltaTime)
{
	Super::Process(DeltaTime);
	GetCapsuleComponent()->SetCapsuleRadius(CurrentCapsuleRadius);
	GetCharacterMovement()->AvoidanceConsiderationRadius = CurrentCapsuleRadius * 2.0f;
	GetCharacterMovement()->bUseRVOAvoidance = bHasAvoidance;
	GetCharacterMovement()->AvoidanceWeight = CurrentAvoidanceWeight;
	GetCapsuleComponent()->SetCollisionProfileName(CollisionName);
	if (bIsFlying) {
		ProcessFlyingUnit(DeltaTime);
		return;
	}
	if (State == EXYZUnitState::DEAD) return;
	
	if (State == EXYZUnitState::MOVING && !GetCharacterMovement()->IsMovingOnGround())
	{
		GetXYZAIController()->RecalculateMove();
	}
	if (State == EXYZUnitState::MOVING || State == EXYZUnitState::ATTACK_MOVING || State == EXYZUnitState::FOLLOWING)
	{
		ScanXYZActorsAhead();
	}
	if (State == EXYZUnitState::ATTACK_MOVING || (State == EXYZUnitState::IDLE && !this->IsA(AXYZWorker::StaticClass())) || State == EXYZUnitState::ATTACKING ||
		State == EXYZUnitState::HOLD)
	{
		if(TargetActor && !GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->DoesActorHasVisionOfActor(this, TargetActor))
		{
			if(State != EXYZUnitState::HOLD)
			{
				GetXYZAIController()->XYZStopMovement();
			}
			TargetActor = nullptr;
			return;
		}
		if (!TargetActor || TargetActor->Health <= 0.0f)
		{
			TargetActor = FindClosestActor(true);
		}
		if (TargetActor)
		{
			AttackMoveTarget();
		}
		if (!TargetActor && State == EXYZUnitState::ATTACKING)
		{
			SetState(EXYZUnitState::IDLE);
		}
	}
	if (State == EXYZUnitState::FOLLOWING)
	{
		if (!TargetActor || TargetActor->Health <= 0.0f)
		{
			GetXYZAIController()->XYZStopMovement();
		}
		else
		{
			GetXYZAIController()->RecalculateMove();
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
		if(!TargetActor && bHasReachedTargetLocation)
		{
			GetXYZAIController()->XYZStopMovement();
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
			TargetActor = FindClosestActor(true);
			DirectionToAttackLocation = (TargetLocation - CurrentLocation).GetSafeNormal();
			NewLocation = CurrentLocation + DirectionToAttackLocation * FlyingSpeed * DeltaSeconds;
			NewRotation = (TargetLocation - NewLocation).Rotation();
			bUpdateLocation = true;
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
		TargetActor = FindClosestActor(true);
		if(TargetActor)
		{
			GetXYZAIController()->XYZAttackMoveToTarget(TargetActor);
		}else
		{
			UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;

			if (MapManager->Grid.Contains(GridCoord) && MapManager->Grid[GridCoord].ActorsInCell.Contains(this))
			{
				TArray<FVector> OtherFlyingUnitLocations;
				TArray<FIntVector2> UnitAreaCoords = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(2,2));
				UnitAreaCoords.Add(GridCoord);

				for(FIntVector2 AreaCoord : UnitAreaCoords)
				{
					if(!MapManager->Grid.Contains(AreaCoord)) continue;
					TSet<AXYZActor*> FlyingUnitsInCoord = MapManager->Grid[AreaCoord].ActorsInCell;
					for (AXYZActor* FlyingUnit : FlyingUnitsInCoord)
					{
						if (!FlyingUnit) continue;
						if (FlyingUnit->bIsFlying &&
							FlyingUnit->State == EXYZUnitState::IDLE &&
							FlyingUnit->TeamId == TeamId &&
							FlyingUnit != this &&
							FVector::Distance(FlyingUnit->GetActorLocation(), GetActorLocation()) < GetCapsuleComponent()->GetScaledCapsuleRadius()*2.0f)
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

					MapManager->AddToUpdateSet(this);

					SetActorLocation(GetActorLocation() - WeightedAvgDirection * 50.0f * DeltaSeconds);
				}
			}
		}
		break;
	case EXYZUnitState::HOLD:
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
			TargetActor = FindClosestActor(true);
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

void AXYZUnit::FlyingAttackMoveTarget()
{
	if(TargetActor->State == EXYZUnitState::DEAD || TargetActor->Health <= 0.0f)
	{
		TargetActor = nullptr;
		return;
	}
	if(IsInAttackRangeOfUnit())
	{
		Attack();
	}
}

bool AXYZUnit::IsInAttackRangeOfUnit()
{
	if (TargetActor &&
		TargetActor != this &&
		TargetActor->State != EXYZUnitState::DEAD &&
		TargetActor->CanAttack(this))
	{
		
		FVector ActorLocation = GetActorLocation();
		FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
		FVector TargetActorLocation = TargetActor->GetActorLocation();
		float TargetActorRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius();
		FVector Direction = TargetActorLocation - ActorLocation;
		Direction.Z = 0;
		Direction.Normalize();

		FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
		float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);
		
		DistanceToTarget -= TargetActorRadius;
		return DistanceToTarget <= AttackRange;
	}
	return false;
}