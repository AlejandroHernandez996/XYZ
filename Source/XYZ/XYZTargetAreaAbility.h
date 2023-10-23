// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZAbilityState.h"
#include "XYZTargetAreaAbility.generated.h"

class AXYZAreaOfEffect;
class AXYZAbilityMarker;
class UXYZBuffAbility;
/**
 * 
 */
UCLASS()
class XYZ_API UXYZTargetAreaAbility : public UXYZAbility
{
	GENERATED_BODY()

public:
	virtual bool Activate() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AXYZAbilityMarker> AbilityMarkerTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AXYZAreaOfEffect> AOETemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AXYZAbilityMarker* ActiveAbilityMarker;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXYZAbilityState AbilityState = EXYZAbilityState::IDLE;
	
	UFUNCTION()
	void SetAbilityState(EXYZAbilityState NewState);
	UFUNCTION()
	void UpdateAbilityMarker();
};
