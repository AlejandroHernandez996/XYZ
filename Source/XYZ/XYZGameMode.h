// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "XYZInputMessage.h"
#include "XYZGameMode.generated.h"

UCLASS(minimalapi)
class AXYZGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AXYZGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	int32 TickCount = 0;
	void QueueInput(const FXYZInputMessage& InputMessage);

	TMap<uint32, TArray<uint32>> TeamResourcesMap;

	TMap<uint32, TArray<uint32>> TeamSupplyMap;

	UPROPERTY()
	class UXYZInputManager* InputManager;
	UPROPERTY()
	class UXYZBlobManager* BlobManager;
	UPROPERTY()
		TArray<class AXYZPlayerController*> PlayerControllers;
	bool bHandleInputQueue;
};



