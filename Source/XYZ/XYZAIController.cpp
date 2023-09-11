// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZAIController.h"
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
        bHasCompletedMove = true;
    }
}
void AXYZAIController::XYZMoveToActor(AXYZActor* Actor) {

    if (!Actor) return;
    MoveToActor(Actor, 50.0f, true, true, false, false);
}
void AXYZAIController::XYZMoveToLocation(FVector TargetLocation) {
    MoveToLocation(TargetLocation, 50.0f, true, true, false, false);
}