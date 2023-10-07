// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActorCount.h"
#include "XYZActorCache.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZActorCache : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FActorCount> ActorCountsByTeamId;
	UFUNCTION()
	void RemoveActorCount(int32 TeamId, int32 ActorId);
	UFUNCTION()
	void AddActorCount(int32 TeamId, int32 ActorId);
	UFUNCTION()
	bool DoesTeamHaveActor(int32 TeamId, int32 ActorId);
};