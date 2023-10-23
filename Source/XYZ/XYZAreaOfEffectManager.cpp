// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAreaOfEffectManager.h"

#include "XYZAreaOfEffect.h"

void UXYZAreaOfEffectManager::Process(float DeltaTime)
{
	for(AXYZAreaOfEffect* AreaOfEffect : ActiveAOEs)
	{
		if(AreaOfEffect)
		{
			AreaOfEffect->Process(DeltaTime);
			if(AreaOfEffect->bIsDone)
			{
				AOEsToDestroy.Add(AreaOfEffect);
			}
		}
	}
	for(AXYZAreaOfEffect* AreaOfEffect : AOEsToDestroy)
	{
		if(AreaOfEffect)
		{
			ActiveAOEs.Remove(AreaOfEffect);
			AreaOfEffect->EndAOE();
		}
		
	}
}

void UXYZAreaOfEffectManager::CreateAOE(TSubclassOf<AXYZAreaOfEffect> AOETemplate, int32 TeamId, FVector TargetLocation)
{
	if (AOETemplate)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			AXYZAreaOfEffect* NewAOE = World->SpawnActor<AXYZAreaOfEffect>(AOETemplate, TargetLocation, FRotator::ZeroRotator);
			if (NewAOE)
			{
				NewAOE->TeamId = TeamId;
				NewAOE->MapManager = MapManager;
				NewAOE->InitBuffs();
				ActiveAOEs.Add(NewAOE);
			}
		}
	}
}