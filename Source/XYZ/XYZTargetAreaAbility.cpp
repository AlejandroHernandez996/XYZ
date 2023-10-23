// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZTargetAreaAbility.h"

#include "XYZActor.h"
#include "XYZAreaOfEffectManager.h"
#include "XYZGameMode.h"
#include "Components/DecalComponent.h"

bool UXYZTargetAreaAbility::Activate()
{
	if(Super::Activate())
	{
		OwningActor->Energy -= EnergyCost;
		GetWorld()->GetAuthGameMode<AXYZGameMode>()->AreaOfEffectManager->CreateAOE(AOETemplate,OwningActor->TeamId, TargetLocation);
		return true;
	}
	return false;
}

void UXYZTargetAreaAbility::SetAbilityState(EXYZAbilityState NewState)
{
	AbilityState = NewState;
}

void UXYZTargetAreaAbility::UpdateAbilityMarker()
{
	if(!AbilityGroundDecal) return;
	switch (AbilityState) {
	case EXYZAbilityState::IDLE:
		AbilityGroundDecal->SetHiddenInGame(true);
		break;
	case EXYZAbilityState::SELECTED:
		AbilityGroundDecal->SetHiddenInGame(false);
		break;
	case EXYZAbilityState::ACTIVATED:
		AbilityGroundDecal->SetHiddenInGame(true);
		break;
	default: ;
	}
}


