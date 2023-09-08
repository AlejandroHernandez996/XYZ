// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZMoveAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZMoveAction : public UXYZAction
{
	GENERATED_BODY()

public:
	virtual void ProcessAction(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Move")
		float TargetLocationThreshold = .5f;

};
