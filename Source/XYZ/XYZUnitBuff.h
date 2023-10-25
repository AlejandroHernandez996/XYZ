// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "XYZStat.h"
#include "UObject/NoExportTypes.h"
#include "XYZUnitBuff.generated.h"

class UXYZBuffAbility;
/**
 * 
 */
UCLASS(Blueprintable)
class XYZ_API UXYZUnitBuff : public UObject , public IProcessable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BuffId = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EXYZStat, float> BuffStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EXYZStat, float> DebuffStats;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BuffDuration = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDrainsEnergy;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnergyDrainPerSecond = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TotalTimeBuffed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AXYZActor* OwnerXYZActor;

	void Process(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable = false;

	UPROPERTY()
	UXYZBuffAbility* OwningAbility;
	
	UFUNCTION()
	void BuffActor(AXYZActor* Actor);
	UFUNCTION()
	void DebuffActor(AXYZActor* Actor);
	void BuffActorStat(EXYZStat Stat, float StatGain, AXYZActor* Actor);

	UPROPERTY()
	bool bFlagForRemoval;
};
