// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZTrainingAbilityAction.h"
#include "XYZActor.h"
#include "XYZBuilding.h"

void UXYZTrainingAbilityAction::ProcessAction(TSet<AXYZActor*> Agents)
{
	AXYZBuilding* SmallestQueueBuilding = nullptr;
	int32 SmallestQueue =  TNumericLimits<int32>::Max();
	
	for (AXYZActor* Actor : Agents) {
		AXYZBuilding* Building = Cast<AXYZBuilding>(Actor);
		if(!Building || Building->State == EXYZUnitState::DEAD || Building->BuildingState != EXYZBuildingState::BUILT) continue;
		
		if (Building && Building->ActorId == ActiveActorId && Building->BuildQueueNum < SmallestQueue) {
			SmallestQueue = Building->BuildQueueNum;
			SmallestQueueBuilding = Building;
		}
	}
	
	if(SmallestQueueBuilding)
	{
		SmallestQueueBuilding->UseAbility(AbilityIndex);
	}
}
