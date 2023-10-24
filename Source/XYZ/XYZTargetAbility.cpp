// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZTargetAbility.h"

#include "Components/DecalComponent.h"

void UXYZTargetAbility::SetAbilityState(EXYZAbilityState NewState)
{
	AbilityState = NewState;
}

void UXYZTargetAbility::UpdateAbilityMarker()
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