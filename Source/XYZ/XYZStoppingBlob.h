// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZBlob.h"
#include "XYZStoppingBlob.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZStoppingBlob : public UXYZBlob
{
	GENERATED_BODY()
public:
	virtual void ProcessBlob() override;
};
