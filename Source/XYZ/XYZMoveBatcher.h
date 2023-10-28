// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "XYZMoveBatcher.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZMoveBatcher : public UObject, public IProcessable
{
	GENERATED_BODY()

public:
	virtual void Process(float DeltaTime) override;

	UPROPERTY()
	int32 BatchSize = 10;

	TSet<TSharedPtr<FXYZMove>> MovesToProcess;
};

USTRUCT()
struct FXYZMove
{
	GENERATED_BODY()

	UPROPERTY()
	class AXYZActor* ActorToMove;
	UPROPERTY()
	class AXYZActor* ActorToTarget;
	UPROPERTY()
	FVector TargetLocation;
};
