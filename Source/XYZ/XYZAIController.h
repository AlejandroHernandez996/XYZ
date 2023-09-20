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

	UPROPERTY()
	FVector CurrentTargetLocation;
	UPROPERTY()
	bool bIsMoving;
	UPROPERTY()
	bool bHasCompletedMove;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
	UFUNCTION()
	void XYZMoveToActor(class AXYZActor* Actor, float AcceptanceRadius = 1.0f);
	UFUNCTION()
	void XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius = 1.0f);
	UFUNCTION()
	void XYZFollowTarget(AXYZActor* Actor, float AcceptanceRadius = 1.0f);
	UFUNCTION()
	void XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius = 1.0f);
	UFUNCTION()
	void XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius = 1.0f);
	UFUNCTION()
		void XYZGatherResource(class AXYZResourceActor* Resource, float AcceptanceRadius = 1.0f);
	UFUNCTION()
		void XYZReturnResource(class AXYZBaseBuilding* Base, float AcceptanceRadius = 1.0f);
	UFUNCTION()
	void XYZStopMovement();
	UFUNCTION()
	void RecalculateMove();
	UFUNCTION()
		void XYZHold();
};
