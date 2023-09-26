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
	virtual void Tick(float DeltaTime);
	UPROPERTY(BlueprintReadOnly)
	int32 MAX_BUILD_QUEUE_SIZE = 6;
	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 BuildQueueNum = 0;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	UPROPERTY(BlueprintReadOnly, Replicated)
		FVector RallyPoint;
	UPROPERTY(BlueprintReadOnly, Replicated)
		FVector SpawnPoint;
	UPROPERTY()
		class AXYZActor* RallyTarget;
	UPROPERTY()
		bool bCanRally;

	TQueue<class UXYZBuildingAbility*> BuildQueue;
	UFUNCTION()
		void EnqueueAbility(class UXYZBuildingAbility* BuildingAbility);
	UPROPERTY(BlueprintReadOnly, Replicated)
		float TimeToBuild = -1.0f;
	UPROPERTY(BlueprintReadOnly, Replicated)
		float TotalBuildTime = -1.0f;
	UFUNCTION()
		void TrainUnit(TSubclassOf<class AXYZActor> UnitTemplate);
	UFUNCTION()
		void ProcessBuildQueue(float DeltaTime);
	UFUNCTION()
		void CancelProduction();
	bool bIsTraining;

	void ProcessActor() override;
};
