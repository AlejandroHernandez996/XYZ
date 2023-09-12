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
        GetPawn<AXYZActor>()->State = EXYZUnitState::IDLE;
    }
}
void AXYZAIController::XYZMoveToActor(AXYZActor* Actor, float AcceptanceRadius) {

    if (!Actor) return;
    MoveToActor(Actor, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->State = EXYZUnitState::MOVING;

}
void AXYZAIController::XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->State = EXYZUnitState::MOVING;
}

void AXYZAIController::XYZStopMovement() {
    StopMovement();
    GetPawn<AXYZActor>()->State = EXYZUnitState::IDLE;
}
