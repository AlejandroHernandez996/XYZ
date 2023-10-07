// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZWorkerAbility.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZWorkerAbility : public UXYZAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class AXYZBuilding> PlacementTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class AXYZBuilding> BuildingTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildTime;
	UPROPERTY()
	class AXYZWorker* OwningWorker;
	UPROPERTY()
	bool bCanCancel = true;
	virtual void Activate() override;

	UPROPERTY()
	FVector BuildingLocation;
};
