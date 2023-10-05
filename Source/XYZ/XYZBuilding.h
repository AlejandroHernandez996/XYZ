// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZBuildingState.h"
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
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly)
		int32 MAX_BUILD_QUEUE_SIZE = 6;
	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 BuildQueueNum = 0;
	UPROPERTY(BlueprintReadOnly, Replicated)
		FVector RallyPoint;
	UPROPERTY(BlueprintReadOnly, Replicated)
		FVector SpawnPoint;
	UPROPERTY()
		class AXYZActor* RallyTarget;
	UPROPERTY()
		bool bCanRally;
	TQueue<class UXYZBuildingAbility*> BuildQueue;

	UPROPERTY()
	EXYZBuildingState BuildingState = EXYZBuildingState::BUILT;
	
	UFUNCTION()
		void EnqueueAbility(class UXYZBuildingAbility* BuildingAbility);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		float TimeToBuild;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		float TotalBuildTime;
	UFUNCTION()
		void TrainUnit(TSubclassOf<class AXYZActor> UnitTemplate);
	UFUNCTION()
		void ProcessBuildQueue(float DeltaTime);
	UFUNCTION()
		void CancelProduction();
	bool bIsTraining;

	UFUNCTION()
	void Build(float DeltaTime);
	
	void Process(float DeltaTime) override;
};
