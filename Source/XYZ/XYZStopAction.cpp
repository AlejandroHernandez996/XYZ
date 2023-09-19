// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZStopAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"

void UXYZStopAction::ProcessAction(TSet<AXYZActor*> Agents)
{
	for (AXYZActor* Agent : Agents) {
		if (Agent && Agent->GetXYZAIController()) {
			Agent->GetXYZAIController()->XYZStopMovement();
		}
	}
}