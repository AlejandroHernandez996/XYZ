// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
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
	class UXYZDeathManager* DeathManager;
	UPROPERTY()
	class UXYZMatchManager* MatchManager;
	UPROPERTY()
	class UXYZMapManager* MapManager;
	UPROPERTY()
		TArray<class AXYZPlayerController*> PlayerControllers;
	bool bHandleInputQueue;
	bool bHasGameStarted;
	bool bHasGameEnded;
	
	void RegisterExistingPlayers();

	UPROPERTY()
		class USessionHandler* SessionHandler;
	UPROPERTY()
		class UUserInfoRetriver* UserRetriever;
	UPROPERTY()
		class UUserStatRetriever* UserStatRetriever;
	UPROPERTY()
		class UUserStatUpdater* UserStatUpdater;
	void PreLogout(APlayerController* InPlayerController);

	UPROPERTY()
	TArray<IProcessable*> Processables;

private:
	bool bIsStartingSession;
	bool bIsCreatingSession;
	bool bRetrivedUsersInfo;
	bool bStartedSesion;

	int32 NumOfPlayers;
	bool bAllExistingPlayersRegistered;

	void PostLogin(APlayerController* InPlayerController) override;


};



