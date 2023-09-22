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
		int32 BuildTime;
	UPROPERTY()
		class AXYZBuilding* OwningBuilding;
	virtual void Activate() override;
};
