﻿#pragma once

#include "CoreMinimal.h"
#include "UpgradeAbilitiesResearched.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeAbilitiesResearched
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<int32> Team1ResearchedAbiltiesAtStage;

	UPROPERTY()
	TArray<int32> Team2ResearchedAbiltiesAtStage;

	void AddResearchedAbility(int32 AbilityId, int32 Stage, int32 TeamId)
	{
		if(!Team1ResearchedAbiltiesAtStage.IsValidIndex(AbilityId) || !Team2ResearchedAbiltiesAtStage.IsValidIndex(AbilityId)) return;
		
		if(TeamId == 0)
		{
			Team1ResearchedAbiltiesAtStage[AbilityId] = Stage;
		}else if (TeamId == 1)
		{
			Team2ResearchedAbiltiesAtStage[AbilityId] = Stage;
		}
	}

	int32 GetCurrentUpgradeStage(int32 AbilityId, int32 TeamId)
	{
		if(!Team1ResearchedAbiltiesAtStage.IsValidIndex(AbilityId) || !Team2ResearchedAbiltiesAtStage.IsValidIndex(AbilityId)) return -1;
		
		if(TeamId == 0)
		{
			return Team1ResearchedAbiltiesAtStage[AbilityId];
		}
		if (TeamId == 1)
		{
			return Team2ResearchedAbiltiesAtStage[AbilityId];
		}
		return -1;
	}
};