// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAbility.h"
#include "XYZTargetLocationAbility.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZTargetLocationAbility : public UXYZAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* AbilityMesh;
	
};
