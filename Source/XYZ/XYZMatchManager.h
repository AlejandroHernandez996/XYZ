// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "XYZMatchManager.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZMatchManager : public UObject, public IProcessable
{
	GENERATED_BODY()
public:
	void Process(float DeltaSeconds);
	UPROPERTY()
	class AXYZGameState* XYZGameState;
	UPROPERTY()
	class AXYZGameMode* XYZGameMode;
	UPROPERTY()
	int32 WinnerIndex = -1;
};
