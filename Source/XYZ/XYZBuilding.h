// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZBuilding.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZBuilding : public AXYZActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
