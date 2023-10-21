// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZUnit.h"
#include "XYZResourceType.h"
#include "XYZWorker.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZWorker : public AXYZUnit
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Gather();
	UFUNCTION()
		void Return();
	UFUNCTION()
	void FlyingGather(float DeltaSeconds);
	UFUNCTION()
	void FlyingReturn(float DeltaSeconds);
	UFUNCTION()
		void FindClosestBase();
	UFUNCTION()
		void FindClosestResource();
	UFUNCTION()
		void StartReturningResource();
	UPROPERTY()
		class AXYZBaseBuilding* ClosestBase;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", Replicated)
		EXYZResourceType HeldResource = EXYZResourceType::NONE;
	UPROPERTY()
		EXYZResourceType ResourceToGather = EXYZResourceType::MINERAL;
	UPROPERTY()
		FTimerHandle GatherTimer;
	UPROPERTY()
		float GatherRate = 2.0f;
	UPROPERTY()
		float TimeToGather = 0.0f;
	UPROPERTY()
		bool bIsGatheringResource;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void SetState(EXYZUnitState State) override;
	UFUNCTION()
	void PlaceBuilding();
	UFUNCTION()
	bool IsWorkerInDistanceToPlace(const FIntVector2& CurrentGridPosition,
	                               const FIntVector2& PlacementCenterGridPosition,
	                               const FIntVector2& PlacementGridSize);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EXYZResourceType, int32> MiningAmountByResourceType;;

	UFUNCTION()
	void ProcessFlyingWorker(float DeltaTime);
	void Process(float DeltaTime) override;

	bool bFirstMineralGathered;

	class UXYZWorkerAbility* ActivePlacementAbility;
};
