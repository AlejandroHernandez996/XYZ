// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "GameFramework/GameModeBase.h"
#include "XYZInputMessage.h"
#include "XYZGameMode.generated.h"

class AXYZGameState;

UCLASS(minimalapi)
class AXYZGameMode : public AGameModeBase, public IProcessable
{
	GENERATED_BODY()

public:
	AXYZGameMode();
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void ProcessWaitingForPlayers();
	
	UFUNCTION()
	void ProcessMatchStarting();
	
	virtual void Process(float DeltaTime) override;
	
	UFUNCTION()
	void ProcessCleanUp();
	
	UFUNCTION()
	void ProcessShutdown();

	virtual void Tick(float DeltaSeconds) override;
	int32 TickCount = 0;
	int32 MAX_PLAYERS = 2;
	float LOADING_TIME = 3.0f;
	int32 RATING_GAIN = 25;
	float TIME_TO_DESTROY_SESSION = 2.0f;
	
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
	class UXYZUpgradeManager* UpgradeManager;
	UPROPERTY()
	class UXYZProjectileManager* ProjectileManager;
	UPROPERTY()
	class UXYZAreaOfEffectManager* AreaOfEffectManager;
	UPROPERTY()
	class UXYZMoveBatcher* MoveBatcher;
	
	UPROPERTY()
	class UXYZActorCache* ActorCache;
	
	UPROPERTY()
		TSet<class AXYZPlayerController*> PlayerControllers;
	TMap<int32, AXYZPlayerController*> TeamIdToPlayerController;
	bool bHandleInputQueue;
	bool bHasGameStarted;
	bool bHasGameEnded;
	bool bHasCleanedUp;
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

	float TimeSinceStart;

	UPROPERTY()
	AXYZGameState* XYZGameState;

};



