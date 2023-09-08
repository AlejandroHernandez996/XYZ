// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAction.h"

void UXYZAction::TryAction(float DeltaTime) {
    if (ActionState == EXYZActionState::QUEUED) {
        StartAction();
    }
    if (!IsFlaggedForDeuque()) {
        ProcessAction(DeltaTime);
    }
}