// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZHoldAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"

void UXYZHoldAction::ProcessAction(TSet<AXYZActor*> Agents)
{
	for (AXYZActor* Agent : Agents) {
		if (Agent && Agent->GetXYZAIController()) {
			Agent->GetXYZAIController()->XYZHold();
		}
	}
}