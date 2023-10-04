// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZPlaceBuildingAction.h"

#include "XYZWorker.h"
#include "XYZWorkerAbility.h"

void UXYZPlaceBuildingAction::ProcessAction(TSet<AXYZActor*> Agents)
{
	AXYZWorker* AvailableWorker = nullptr;
	
	for (AXYZActor* Actor : Agents) {
		if(!Actor || Actor->State == EXYZUnitState::DEAD) continue;
		
		AXYZWorker* Worker = Cast<AXYZWorker>(Actor);
		if (Worker && Worker->ActorId == ActiveActorId && Worker->State != EXYZUnitState::PLACING && Worker->State != EXYZUnitState::BUILDING) {
			AvailableWorker = Worker;
		}
	}
	
	if(AvailableWorker)
	{
		Cast<UXYZWorkerAbility>(AvailableWorker->Abilities[AbilityIndex])->BuildingLocation = TargetLocation;
		AvailableWorker->UseAbility(AbilityIndex);
	}
}

bool UXYZPlaceBuildingAction::HasAgentComplete(AXYZActor* Agent)
{
	if(!Agent) return true;
	
	return Agent->State != EXYZUnitState::PLACING && Agent->State != EXYZUnitState::BUILDING;
}
