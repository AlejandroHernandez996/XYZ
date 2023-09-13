// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZAIController.h"
#include "Components/CapsuleComponent.h"
#include "XYZActor.h"

void AXYZAIController::BeginPlay()
{
    Super::BeginPlay();

    if (GetPathFollowingComponent())
    {
        GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AXYZAIController::OnMoveCompleted);
    }
}

void AXYZAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.Code == EPathFollowingResult::Success)
    {
        GetPawn<AXYZActor>()->SetState(EXYZUnitState::IDLE);
        bIsMoving = false;
        GetPawn<AXYZActor>()->CapsuleRadius = 50.0f;
    }
}

void AXYZAIController::XYZMoveToActor(AXYZActor* Actor, float AcceptanceRadius) {
    if (!Actor) return;
    MoveToActor(Actor, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::MOVING);
    CurrentTargetLocation = Actor->GetActorLocation();
    bIsMoving = true;
    GetPawn<AXYZActor>()->CapsuleRadius = 25.0f;
}

void AXYZAIController::XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>()) return;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::MOVING);
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;

    GetPawn<AXYZActor>()->CapsuleRadius = 25.0f;
}

void AXYZAIController::XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>()) return;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::ATTACK_MOVING);
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;
    GetPawn<AXYZActor>()->CapsuleRadius = 25.0f;
}

void AXYZAIController::XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>() || !Actor) return;
    MoveToActor(Actor, AcceptanceRadius, true, true, false, false);
    CurrentTargetLocation = Actor->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::ATTACK_MOVING);
    GetPawn<AXYZActor>()->TargetActor = Actor;
    bIsMoving = true;
    GetPawn<AXYZActor>()->CapsuleRadius = 25.0f;
}

void AXYZAIController::XYZStopMovement() {
    if (!GetPawn<AXYZActor>()) return;
    StopMovement();
    CurrentTargetLocation = GetPawn<AXYZActor>()->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::IDLE);
    bIsMoving = false;
    GetPawn<AXYZActor>()->CapsuleRadius = 50.0f;
}

void AXYZAIController::RecalculateMove() {
    if (!GetPawn<AXYZActor>()) return;
    switch (GetPawn<AXYZActor>()->State) {
    case EXYZUnitState::IDLE :
        XYZStopMovement();
        break;
    case EXYZUnitState::MOVING:
        XYZMoveToLocation(CurrentTargetLocation);
        break;
    case EXYZUnitState::ATTACK_MOVING:
        XYZAttackMoveToLocation(CurrentTargetLocation);
        break;
    }
}