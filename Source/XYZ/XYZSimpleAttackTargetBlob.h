// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZBlob.h"
#include "XYZSimpleAttackTargetBlob.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZSimpleAttackTargetBlob : public UXYZBlob
{
	GENERATED_BODY()
public:
	virtual void ProcessBlob() override;
};
