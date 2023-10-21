// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZWorkerAbility.h"

#include "SoundTypes.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "XYZWorker.h"

bool UXYZWorkerAbility::Activate()
{
	if(Super::Activate())
	{
		AXYZGameState* XYZGameState = OwningWorker->GetWorld()->GetGameState<AXYZGameState>();
		AXYZGameMode* XYZGameMode = OwningWorker->GetWorld()->GetAuthGameMode<AXYZGameMode>();

		if(XYZGameState->MineralsByTeamId[OwningWorker->TeamId] >= MineralCost && XYZGameState->GasByTeamId[OwningWorker->TeamId] >= GasCost)
		{
			OwningWorker->TargetLocation = BuildingLocation;
			OwningWorker->ActivePlacementAbility = this;
			XYZGameState->MineralsByTeamId[OwningWorker->TeamId] -= MineralCost;
			XYZGameState->GasByTeamId[OwningWorker->TeamId] -= GasCost;
			OwningWorker->SetState(EXYZUnitState::PLACING);
			return true;
		}
		if(XYZGameMode && XYZGameMode->TeamIdToPlayerController.Contains(OwningWorker->TeamId))
		{
			XYZGameMode->TeamIdToPlayerController[OwningWorker->TeamId]->PlaySound(ESoundTypes::MINERALS);
		}
	}
	return false;
}
