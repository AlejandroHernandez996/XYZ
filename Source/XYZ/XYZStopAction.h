// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZStopAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZStopAction : public UXYZAction
{
	GENERATED_BODY()

public:
	virtual void ProcessAction(float DeltaTime) override;
};
