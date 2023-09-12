// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZStoppingBlob.h"
#include "XYZAIController.h"

void UXYZStoppingBlob::ProcessBlob()
{
    if (ActionQueue.IsEmpty() || AgentsInBlob.IsEmpty()) return;
    for (AXYZActor* Agent : AgentsInBlob) {
        Agent->GetXYZAIController()->XYZStopMovement();
    }
    AgentsInBlob.Empty();
    ActionQueue.Empty();
}