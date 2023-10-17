// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZFlyingAIController.h"

#include "XYZActor.h"
#include "XYZUnitState.h"

void AXYZFlyingAIController::XYZMoveToActor(AXYZActor* Actor, float AcceptanceRadius)
{
	AXYZActor* OwningActor = GetXYZActor();
	if(!OwningActor || !Actor || OwningActor == Actor)
	{
		XYZStopMovement();
		return;
	}
	XYZMoveToLocation(Actor->GetActorLocation());
}

void AXYZFlyingAIController::XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius)
{
	AXYZActor* OwningActor = GetXYZActor();
	if(!OwningActor) return;
	GetXYZActor()->SetState(EXYZUnitState::MOVING);
	CurrentTargetLocation = TargetLocation;
	OwningActor->TargetLocation = TargetLocation;
	bIsMoving = true;
}

void AXYZFlyingAIController::XYZFollowTarget(AXYZActor* Actor, float AcceptanceRadius)
{
	AXYZActor* OwningActor = GetXYZActor();
	if (!OwningActor || !Actor || GetXYZActor() == Actor) {
		XYZStopMovement();
		return;
	}
	GetXYZActor()->SetState(EXYZUnitState::FOLLOWING);
	GetXYZActor()->TargetActor = Actor;
	bIsMoving = true;
}

void AXYZFlyingAIController::XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius)
{
	AXYZActor* OwningActor = GetXYZActor();
	if (!OwningActor) return;
	GetXYZActor()->SetState(EXYZUnitState::ATTACK_MOVING);
	CurrentTargetLocation = TargetLocation;
	OwningActor->TargetLocation = TargetLocation;
	bIsMoving = true;
}

void AXYZFlyingAIController::XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius)
{
	AXYZActor* OwningActor = GetXYZActor();
	if (!OwningActor || !Actor || GetXYZActor() == Actor) {
		XYZStopMovement();
		return;
	}
	CurrentTargetLocation = Actor->GetActorLocation();
	GetXYZActor()->SetState(EXYZUnitState::ATTACKING);
	GetXYZActor()->TargetActor = Actor;
	bIsMoving = true;
}

void AXYZFlyingAIController::XYZStopMovement()
{
	AXYZActor* OwningActor = GetXYZActor();
	if (!OwningActor) return;
	bIsMoving = false;
	CurrentTargetLocation = OwningActor->GetActorLocation();
	OwningActor->TargetLocation = CurrentTargetLocation;
	OwningActor->SetState(EXYZUnitState::IDLE);
}

void AXYZFlyingAIController::XYZHold()
{
	AXYZActor* OwningActor = GetXYZActor();
	if (!OwningActor) return;
	XYZStopMovement();
	GetXYZActor()->SetState(EXYZUnitState::HOLD);
	CurrentTargetLocation = GetXYZActor()->GetActorLocation();
	OwningActor->TargetLocation = CurrentTargetLocation;
}
