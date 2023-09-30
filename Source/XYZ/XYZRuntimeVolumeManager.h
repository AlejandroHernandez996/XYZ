// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZRuntimeVolumeManager.generated.h"

UCLASS()
class XYZ_API AXYZRuntimeVolumeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXYZRuntimeVolumeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ARuntimeVirtualTextureVolume*> RuntimeVolumes;
	bool bStopTickFlag;
};
