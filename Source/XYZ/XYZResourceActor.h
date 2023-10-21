// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZResourceType.h"
#include "XYZWorker.h"
#include "XYZResourceActor.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZResourceActor : public AXYZActor
{
	GENERATED_BODY()
public:
	virtual void Process(float DeltaSeconds) override;
	UFUNCTION()
	void AddWorker(AXYZWorker* Worker);
	UFUNCTION()
	void RemoveWorker(const AXYZWorker* Worker);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXYZResourceType ResourceType = EXYZResourceType::MINERAL;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RESOURCE_CAPACITY = 2;
	UPROPERTY()
	TMap<AXYZWorker*, bool> Workers;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", Replicated)
	int32 CurrentWorkers = 0;
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
