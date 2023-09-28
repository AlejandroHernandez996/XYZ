// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUnit.h"

#include "XYZAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AXYZUnit::Process(float DeltaTime)
{
	Super::Process(DeltaTime);
	if (State == EXYZUnitState::DEAD) return;
	GetCapsuleComponent()->SetCapsuleRadius(CurrentCapsuleRadius);
	GetCharacterMovement()->AvoidanceConsiderationRadius = CurrentCapsuleRadius * 1.25f;
	GetCharacterMovement()->bUseRVOAvoidance = bHasAvoidance;
	GetCapsuleComponent()->SetCollisionProfileName(CollisionName);

	
	if (State == EXYZUnitState::MOVING && !GetCharacterMovement()->IsMovingOnGround())
	{
		GetXYZAIController()->RecalculateMove();
	}
	if (State == EXYZUnitState::MOVING || State == EXYZUnitState::ATTACK_MOVING || State == EXYZUnitState::FOLLOWING)
	{
		ScanXYZActorsAhead();
	}
	if (State == EXYZUnitState::ATTACK_MOVING || State == EXYZUnitState::IDLE || State == EXYZUnitState::ATTACKING ||
		State == EXYZUnitState::HOLD)
	{
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
