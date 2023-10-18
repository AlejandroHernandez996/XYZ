#pragma once

#include "CoreMinimal.h"
#include "UpgradeAbilitiesResearched.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeAbilitiesResearched
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<int32> Team1ResearchedAbiltiesAtStage;

	UPROPERTY(BlueprintReadOnly)
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

 	bool HasUpgradeResearched(int32 TeamId, int32 AbilityId)
	{
		if(!Team1ResearchedAbiltiesAtStage.IsValidIndex(AbilityId) || !Team2ResearchedAbiltiesAtStage.IsValidIndex(AbilityId)) return false;
		
		if(TeamId == 0)
		{
			return Team1ResearchedAbiltiesAtStage[AbilityId] > -1;
		}
		if (TeamId == 1)
		{
			return Team2ResearchedAbiltiesAtStage[AbilityId] > -1;
		}

		return false;
	}

	bool UpgradeAbilityIsAtMaxStage(int32 TeamId, int32 AbilityId, int32 MaxStage)
	{
		if(TeamId == 0)
		{
			return Team1ResearchedAbiltiesAtStage[AbilityId] >= MaxStage;
		}
		if (TeamId == 1)
		{
			return Team2ResearchedAbiltiesAtStage[AbilityId] >=  MaxStage;
		}
		return false;
	}
};