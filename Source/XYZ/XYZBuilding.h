// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZBuilding.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZBuilding : public AXYZActor
{
	GENERATED_BODY()
public:
	int32 MAX_BUILD_QUEUE_SIZE = 6;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	UPROPERTY(Replicated)
		FVector RallyPoint;
	UPROPERTY()
		class AXYZActor* RallyTarget;
	UPROPERTY()
		bool bCanRally;
	UPROPERTY()
	TArray<class UXYZBuildingAbility*> BuildQueue;
	UPROPERTY()
		float TimeToBuild;
	UPROPERTY()
		int32 SupplyGain;
};
