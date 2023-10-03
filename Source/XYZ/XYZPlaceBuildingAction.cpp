// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZPlaceBuildingAction.h"

#include "XYZWorker.h"

void UXYZPlaceBuildingAction::ProcessAction(TSet<AXYZActor*> Agents)
{
	AXYZWorker* AvailableWorker = nullptr;
	
	for (AXYZActor* Actor : Agents) {
		if(!Actor || Actor->State == EXYZUnitState::DEAD) continue;
		
		AXYZWorker* Worker = Cast<AXYZWorker>(Actor);
		if (Worker && Worker->ActorId == ActiveActorId && Worker->State != EXYZUnitState::BUILDING) {
			AvailableWorker = Worker;
		}
	}
	
	if(AvailableWorker)
	{
		AvailableWorker->UseAbility(AbilityIndex);
	}
}
