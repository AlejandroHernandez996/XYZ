// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZTargetAbility.h"
#include "XYZTargetAreaAbility.generated.h"

class AXYZAreaOfEffect;
class AXYZAbilityMarker;
class UXYZBuffAbility;
/**
 * 
 */
UCLASS()
class XYZ_API UXYZTargetAreaAbility : public UXYZTargetAbility
{
	GENERATED_BODY()

public:
	virtual bool Activate() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AXYZAreaOfEffect> AOETemplate;
};
