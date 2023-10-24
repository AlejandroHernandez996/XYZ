// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZAbilityState.h"
#include "XYZTargetAbility.generated.h"

class AXYZAbilityMarker;
/**
 * 
 */
UCLASS(Abstract)
class XYZ_API UXYZTargetAbility : public UXYZAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AXYZAbilityMarker> AbilityMarkerTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AXYZAbilityMarker* ActiveAbilityMarker;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXYZAbilityState AbilityState = EXYZAbilityState::IDLE;
	
	UFUNCTION()
	virtual void SetAbilityState(EXYZAbilityState NewState);
	UFUNCTION()
	virtual void UpdateAbilityMarker();
};
