// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZUnit.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZUnit : public AXYZActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cost")
		int32 SupplyCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cost")
		int32 GasCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cost")
		int32 MineralCost;
};
