// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZBuffAbility.generated.h"

class UXYZUnitBuff;
/**
 * 
 */
UCLASS(Blueprintable)
class XYZ_API UXYZBuffAbility : public UXYZAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UXYZUnitBuff> BuffTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<int32> RequiredUpgradeIds;

	virtual bool Activate() override;
};
