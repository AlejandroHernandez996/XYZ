// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZStopAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"

void UXYZStopAction::ProcessAction(float DeltaTime)
{
    if (!Actor) {
        CancelAction();
        return;
    }
    Actor->GetController<AXYZAIController>()->StopMovement();
    CompleteAction();
}