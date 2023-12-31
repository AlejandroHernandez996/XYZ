// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZStopAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "XYZGameMode.h"
#include "XYZMoveBatcher.h"

void UXYZStopAction::ProcessAction(TSet<AXYZActor*> Agents)
{
	for (AXYZActor* Agent : Agents) {
		if (Agent && Agent->GetXYZAIController()) {
			UXYZMoveBatcher* MoveBatcher = Agent->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MoveBatcher;
			Agent->SetState(EXYZUnitState::IDLE);
			MoveBatcher->RemoveActorFromBatch(Agent);
			Agent->GetXYZAIController()->XYZStopMovement();
		}
	}
}
