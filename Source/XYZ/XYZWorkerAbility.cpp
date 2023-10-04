// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZWorkerAbility.h"

#include "XYZGameState.h"
#include "XYZWorker.h"

void UXYZWorkerAbility::Activate()
{
	AXYZGameState* XYZGameState = OwningWorker->GetWorld()->GetGameState<AXYZGameState>();

	if(XYZGameState->MineralsByTeamId[OwningWorker->TeamId] >= MineralCost)
	{
		OwningWorker->TargetLocation = BuildingLocation;
		OwningWorker->ActivePlacementAbility = this;
		XYZGameState->MineralsByTeamId[OwningWorker->TeamId] -= MineralCost;
		OwningWorker->SetState(EXYZUnitState::PLACING);
	}
}
