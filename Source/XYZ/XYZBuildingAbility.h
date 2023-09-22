// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZBuildingAbility.generated.h"

UCLASS()
class XYZ_API UXYZBuildingAbility : public UXYZAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TSubclassOf<class AXYZActor> UnitTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BuildTime;
	UPROPERTY()
		class AXYZBuilding* OwningBuilding;
	UPROPERTY()
		bool bCanCancel = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MineralCost = 0;
	virtual void Activate() override;
};
