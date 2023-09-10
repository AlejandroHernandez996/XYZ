// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "XYZAIController.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
	bool bIsMoving;
	bool bHasCompletedMove;
};