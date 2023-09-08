// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZStopAction.h"

void UXYZStopAction::ProcessAction(float DeltaTime)
{
    if (ActionState != EXYZActionState::IN_PROGRESS)
    {
        return;
    }

    if (!Actor)
    {
        CancelAction();
        return;
    }

    CompleteAction();
}