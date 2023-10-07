// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAbility.h"

#include "SoundTypes.h"
#include "XYZActor.h"
#include "XYZActorCache.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"

bool UXYZAbility::Activate()
{

	if(GetWorld() && OwningActor)
	{
		AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();
		if(GameMode && GameMode->ActorCache->ActorCountsByTeamId.IsValidIndex(OwningActor->TeamId))
		{
			bool bHasRequirement = true;
			for(const auto RequiredActorIds : ActorRequirements)
			{
				bHasRequirement = bHasRequirement && GameMode->ActorCache->DoesTeamHaveActor(OwningActor->TeamId, RequiredActorIds.Key);
			}
			if(bHasRequirement)
			{
				return true;
			}
		}
		if(GameMode && GameMode->TeamIdToPlayerController.Contains(OwningActor->TeamId))
		{
			GameMode->TeamIdToPlayerController[OwningActor->TeamId]->PlaySound(ESoundTypes::UPGRADE);
		}
	}
	return false;
}
