// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZMatchManager.h"
#include "XYZGameState.h"
#include "XYZActor.h"
#include "XYZBuilding.h"
#include "XYZGameMode.h"

void UXYZMatchManager::Process()
{
	TArray<bool> bPlayerHasABuilding = {false, false};
	TArray<AXYZActor*> Actors;
	if(!XYZGameState) return;
	XYZGameState->ActorsByUID.GenerateValueArray(Actors);
	if(Actors.IsEmpty()) return;
	for(AXYZActor* Actor : Actors)
	{
		if(Actor)
		{
			if(Actor->IsA(AXYZBuilding::StaticClass()) && Actor->State != EXYZUnitState::DEAD)
			{
				bPlayerHasABuilding[Actor->TeamId] = true;
			}
		}
	}

	if(!bPlayerHasABuilding[0] || !bPlayerHasABuilding[1])
	{
		XYZGameMode->bHasGameEnded = true;
		XYZGameState->bHasGameEnded = true;
	}
}
