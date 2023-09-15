// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZBlob.h"
#include "XYZSimpleFollowBlob.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZSimpleFollowBlob : public UXYZBlob
{
	GENERATED_BODY()
	
public:
	virtual void ProcessBlob() override;
	
};
