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
		FTimerHandle GatherTimer;
	UPROPERTY()
		float GatherRate = 2.0f;
	UPROPERTY()
		float TimeToGather = 0.0f;
	UPROPERTY()
		bool bIsGatheringResource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UStaticMeshComponent* FloatingMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float FloatAmplitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float FloatSpeed;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void SetState(EXYZUnitState State) override;
	UFUNCTION()
	void PlaceBuilding();
	void Process(float DeltaTime) override;

	bool bFirstMineralGathered;

	class UXYZWorkerAbility* ActivePlacementAbility;
};
