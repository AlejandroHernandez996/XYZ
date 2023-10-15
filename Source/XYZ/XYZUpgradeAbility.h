// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZBuildingAbility.h"
#include "XYZStat.h"
#include "XYZUpgradeAbility.generated.h"

UCLASS(Blueprintable)
class XYZ_API UXYZUpgradeAbility : public UXYZBuildingAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<int32> AffectedActorIds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EXYZStat, float> StatGainMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentStage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxStage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TeamId = -1;

	UFUNCTION()
	void UpgradeActor(class AXYZActor* Actor);

	UFUNCTION()
	void UpgradeActorStat(EXYZStat Stat, int32 StatGain, AXYZActor* Actor);

	UFUNCTION()
	UXYZUpgradeAbility* DeepCopy();
};
