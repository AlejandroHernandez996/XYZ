// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbilityAction.h"
#include "XYZAction.h"
#include "XYZPlaceBuildingAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZPlaceBuildingAction : public UXYZAbilityAction
{
	GENERATED_BODY()
	void ProcessAction(TSet<AXYZActor*> Agents) override;
};
