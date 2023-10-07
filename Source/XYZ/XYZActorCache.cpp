// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZActorCache.h"

void UXYZActorCache::RemoveActorCount(int32 TeamId, int32 ActorId)
{
	if(!ActorCountsByTeamId.IsValidIndex(TeamId)) return;

	if(ActorCountsByTeamId[TeamId].ActorCounts.Contains(ActorId))
	{
		ActorCountsByTeamId[TeamId].ActorCounts[ActorId] -= FMath::Clamp(1, 0, 1000);
	}
}

void UXYZActorCache::AddActorCount(int32 TeamId, int32 ActorId)
{
	if(!ActorCountsByTeamId.IsValidIndex(TeamId)) return;
	
	if(!ActorCountsByTeamId[TeamId].ActorCounts.Contains(ActorId))
	{
		ActorCountsByTeamId[TeamId].ActorCounts.Add(ActorId,1);
	}else
	{
		ActorCountsByTeamId[TeamId].ActorCounts[ActorId] += 1;
	}
}

bool UXYZActorCache::DoesTeamHaveActor(int32 TeamId, int32 ActorId)
{
	if(!ActorCountsByTeamId.IsValidIndex(TeamId)) return false;

	return ActorCountsByTeamId[TeamId].ActorCounts.Contains(ActorId) && ActorCountsByTeamId[TeamId].ActorCounts[ActorId] > 0;
}
