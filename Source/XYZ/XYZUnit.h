// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZUnit.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZUnit : public AXYZActor
{
	GENERATED_BODY()
public:
	void Tick(float DeltaTime);
	void Process(float DeltaSeconds) override;
	UFUNCTION()
	void FlyingAttackMoveTarget();
	UFUNCTION()
	void ProcessFlyingUnit(float DeltaSeconds);
	void FlyToLocation(FVector FlyLocation);
	void UpdateCollision();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TrailingDistance = 100.0f;
};
