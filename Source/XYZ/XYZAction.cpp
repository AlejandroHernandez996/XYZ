// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "XYZUnitState.h"

void UXYZAction::TryAction(float DeltaTime) {
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    if (!AIController) {
        CancelAction();
        return;
    }
    if (ActionState == EXYZActionState::QUEUED) {
        StartAction();
    }
    if (!IsFlaggedForDeuque()) {
        ProcessAction(DeltaTime);
    }
}

void UXYZAction::CompleteAction() {
    ActionState = EXYZActionState::COMPLETE;
    Actor->State = EXYZUnitState::IDLE;
}

void UXYZAction::CancelAction() {
    ActionState = EXYZActionState::CANCELLED;
    Actor->State = EXYZUnitState::IDLE;
}

void UXYZAction::StartAction() {
    ActionState = EXYZActionState::IN_PROGRESS;
}
