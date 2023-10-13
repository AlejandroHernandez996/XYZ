// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUnit.h"

#include "XYZAIController.h"
#include "XYZGameMode.h"
#include "XYZWorker.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XYZMapManager.h"

void AXYZUnit::Process(float DeltaTime)
{
	Super::Process(DeltaTime);
	GetCapsuleComponent()->SetCapsuleRadius(CurrentCapsuleRadius);
	GetCharacterMovement()->AvoidanceConsiderationRadius = CurrentCapsuleRadius * 1.25f;
	GetCharacterMovement()->bUseRVOAvoidance = bHasAvoidance;
	GetCapsuleComponent()->SetCollisionProfileName(CollisionName);
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
			GetXYZAIController()->StopMovement();
		}
		else
		{
			GetXYZAIController()->RecalculateMove();
		}
	}
}
