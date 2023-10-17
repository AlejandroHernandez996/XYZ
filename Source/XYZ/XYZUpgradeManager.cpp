// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUpgradeManager.h"

#include "XYZGameState.h"

void UXYZUpgradeManager::Process(float DeltaTime)
{
	if(GameState)
	{
		TArray<AXYZActor*> Actors;
		GameState->ActorsByUID.GenerateValueArray(Actors);

		for(UXYZUpgradeAbility* AbilityToRemove : UpgradeAbilitiesToRemove)
		{
			if(!AbilityToRemove) continue;
			UpgradeAbilities.Remove(AbilityToRemove);
		}
		for(AXYZActor* Actor : Actors)
		{
			if(!Actor) continue;
			if(UpgradesByTeam.IsValidIndex(Actor->TeamId))
			{
				for(UXYZUpgradeAbility* AbilityToRemove : UpgradeAbilitiesToRemove)
				{
					if(Actor->ActiveUpgradeIds.Contains(AbilityToRemove->ID) && Actor->TeamId == AbilityToRemove->TeamId)
					{
						Actor->ActiveUpgradeIds.Remove(AbilityToRemove->ID);
					}
				}
				for(UXYZUpgradeAbility* Ability : UpgradeAbilities)
				{
					if(!Ability) continue;
					if(!Actor->ActiveUpgradeIds.Contains(Ability->ID) &&
						(Ability->AffectedActorIds.Contains(Actor->ActorId) || Ability->AffectedActorIds.IsEmpty()) &&
						Ability->TeamId == Actor->TeamId)
					{
						Actor->ActiveUpgradeIds.Add(Ability->ID);
						Ability->UpgradeActor(Actor);
					}
				}
			}
		}
		UpgradeAbilitiesToRemove.Empty();
	}
}


bool UXYZUpgradeManager::ContainsUpgrade(UXYZUpgradeAbility* UpgradeAbility)
{
	if(!UpgradeAbility || !UpgradesByTeam.IsValidIndex(UpgradeAbility->TeamId)) return true;

	return UpgradesByTeam[UpgradeAbility->TeamId].Contains(UpgradeAbility->ID);
}

bool UXYZUpgradeManager::HasResearched(int32 AbilityId, int32 TeamId)
{
	return UpgradesByTeam.IsValidIndex(TeamId) && UpgradesByTeam[TeamId].Contains(AbilityId);
}

bool UXYZUpgradeManager::IsUpgradeBeingResearched(UXYZUpgradeAbility* UpgradeAbility)
{
	if(!UpgradeAbility || !UpgradesInResearch.IsValidIndex(UpgradeAbility->TeamId)) return true;

	return UpgradesInResearch[UpgradeAbility->TeamId].Contains(UpgradeAbility->ID);
}

void UXYZUpgradeManager::RemoveUpgradeFromResearch(UXYZUpgradeAbility* UpgradeAbility)
{
	if(!UpgradeAbility ||
		!UpgradesInResearch.IsValidIndex(UpgradeAbility->TeamId) ||
		!UpgradesInResearch[UpgradeAbility->TeamId].Contains(UpgradeAbility->ID)) return;

	UpgradesInResearch[UpgradeAbility->TeamId].Remove(UpgradeAbility->ID);
}

void UXYZUpgradeManager::AddUpgradeToResearch(UXYZUpgradeAbility* UpgradeAbility)
{
	if(!UpgradeAbility) return;
	
	if(UpgradesInResearch.IsValidIndex(UpgradeAbility->TeamId))
	{
		UpgradesInResearch[UpgradeAbility->TeamId].Add(UpgradeAbility->ID);
	}
}

void UXYZUpgradeManager::AddUpgradeAbility(UXYZUpgradeAbility* UpgradeAbility)
{
	if(!UpgradeAbility || !UpgradesByTeam.IsValidIndex(UpgradeAbility->TeamId)) return;

	if(UpgradesByTeam[UpgradeAbility->TeamId].Contains(UpgradeAbility->ID))
	{
		if(UXYZUpgradeAbility* PreviousStageAbility = UpgradesByTeam[UpgradeAbility->TeamId][UpgradeAbility->ID])
		{
			UpgradeAbilitiesToRemove.Add(PreviousStageAbility);
			UpgradesByTeam[UpgradeAbility->TeamId].Remove(UpgradeAbility->ID);
		}
	}
		
	UXYZUpgradeAbility* AbilityDeepCopy = UpgradeAbility->DeepCopy();
	UpgradeAbilities.Add(AbilityDeepCopy);
	UpgradesByTeam[UpgradeAbility->TeamId].Add(UpgradeAbility->ID, AbilityDeepCopy);
	GameState->UpgradeAbilitiesResearched.AddResearchedAbility(UpgradeAbility->ID, UpgradeAbility->CurrentStage, UpgradeAbility->TeamId);
}
