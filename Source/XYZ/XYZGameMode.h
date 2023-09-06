// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "XYZActor.h"
#include "XYZInputMessage.h"
#include "XYZGameMode.generated.h"

UCLASS(minimalapi)
class AXYZGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AXYZGameMode();
	virtual void BeginPlay() override;
	void QueueInput(const FXYZInputMessage& InputMessage);
	TMap<uint32, TArray<uint32>> TeamResourcesMap;
	TMap<uint32, TArray<uint32>> TeamSupplyMap;
	class UXYZInputManager* InputManager;
};



