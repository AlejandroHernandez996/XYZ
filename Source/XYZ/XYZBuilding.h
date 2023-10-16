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
	AXYZBuilding();

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
	UPROPERTY(BlueprintReadOnly)
		FVector ValidSpawnPoint;
	UPROPERTY()
		class AXYZActor* RallyTarget;
	virtual void ShowDecal(bool bShowDecal, EXYZDecalType DecalType) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanRally;
	UPROPERTY()
	bool bShowRallyPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAttack;
	UFUNCTION()
	void BuildingAttack();
	
	TArray<class UXYZBuildingAbility*> BuildQueue;
	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<int32> BuildQueueId;
	UPROPERTY(Replicated)
	FVector BuildingSpawnLocation;

	UPROPERTY(Replicated)
	bool bIsSpawned;

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
		void ResearchUpgrade(UXYZUpgradeAbility* UpgradeAbility);
	UFUNCTION()
	bool HasValidSpawnPoint();
	UFUNCTION()
		void ProcessBuildQueue(float DeltaTime);
	UFUNCTION()
		void CancelProduction();
	UFUNCTION()
	void CancelProductionAtIndex();
	UPROPERTY()
	int32 CancelProductionIndex = -1;
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bIsTraining;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D GridSize = FVector2D(1,1);
	
	UFUNCTION()
	void Build(float DeltaTime);

	void Process(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Placement")
	TArray<UMaterialInterface*> PlacementMaterials;

	UFUNCTION()
	void ClearProduction();
};
