// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAIController.h"
#include "XYZFlyingAIController.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZFlyingAIController : public AXYZAIController
{
	GENERATED_BODY()
	void XYZMoveToActor(class AXYZActor* Actor, float AcceptanceRadius = 1.0f) override;
	void XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius = 1.0f) override;
	void XYZFollowTarget(AXYZActor* Actor, float AcceptanceRadius = 1.0f) override;
	void XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius = 1.0f) override;
	void XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius = 1.0f) override;
	void XYZGatherResource(AXYZResourceActor* Resource, float AcceptanceRadius = 1.0f) override;
	void XYZReturnResource(AXYZBaseBuilding* Base, float AcceptanceRadius = 1.0f) override;
	void XYZStopMovement() override;
	void XYZHold() override;

};
