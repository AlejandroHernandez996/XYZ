// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZMatchManager.h"
#include "XYZGameState.h"
#include "XYZActor.h"
#include "XYZBuilding.h"
#include "XYZGameMode.h"

void UXYZMatchManager::Process(float DeltaSeconds)
{
	TArray bPlayerHasABuilding = {false, false};
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

	for(int i = 0;i < bPlayerHasABuilding.Num();i++)
	{
		if(!bPlayerHasABuilding[i])
		{
			XYZGameMode->bHasGameEnded = !bPlayerHasABuilding[i];
			XYZGameState->bHasGameEnded = !bPlayerHasABuilding[i];

			WinnerIndex = i == 0 ? 1 : 0;
			LoserIndex = i;
			break;
		}
	}
}
