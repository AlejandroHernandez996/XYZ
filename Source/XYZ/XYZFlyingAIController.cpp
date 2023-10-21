// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZFlyingAIController.h"

#include "XYZActor.h"
#include "XYZBaseBuilding.h"
#include "XYZBuilding.h"
#include "XYZResourceActor.h"
#include "XYZUnitState.h"
#include "XYZWorker.h"

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
	if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && GetXYZActor()->IsA(AXYZResourceActor::StaticClass())) {
		XYZGatherResource(Cast<AXYZResourceActor>(GetXYZActor()));
		return;
	}
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
	if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && Cast<AXYZWorker>(GetXYZActor())->HeldResource != EXYZResourceType::NONE && Actor->IsA(AXYZBaseBuilding::StaticClass())) {
		Cast<AXYZWorker>(GetXYZActor())->StartReturningResource();
		Cast<AXYZWorker>(GetXYZActor())->FindClosestBase();
		if (Cast<AXYZWorker>(GetXYZActor())->ClosestBase) {
			XYZReturnResource(Cast<AXYZWorker>(GetXYZActor())->ClosestBase);
		}
		return;
	}
	if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && Actor->IsA(AXYZResourceActor::StaticClass())) {
		XYZGatherResource(Cast<AXYZResourceActor>(Actor));
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

void AXYZFlyingAIController::XYZGatherResource(AXYZResourceActor* Resource, float AcceptanceRadius)
{
	if (!GetXYZActor() || !Resource || !GetXYZActor()->IsA(AXYZWorker::StaticClass())) {
		XYZStopMovement();
		return;
	}
	if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
		return;
	}
	GetXYZActor()->SetState(EXYZUnitState::GATHERING);
	Cast<AXYZWorker>(GetXYZActor())->ResourceToGather = Resource->ResourceType;
	GetXYZActor()->TargetActor = Resource;
	bIsMoving = true;
}

void AXYZFlyingAIController::XYZReturnResource(AXYZBaseBuilding* Base, float AcceptanceRadius)
{
	if (!GetXYZActor() || !Base || !GetXYZActor()->IsA(AXYZWorker::StaticClass())) {
		XYZStopMovement();
		return;
	}
	if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
		return;
	}
	GetXYZActor()->SetState(EXYZUnitState::RETURNING);
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
