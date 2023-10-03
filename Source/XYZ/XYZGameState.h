// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZMatchState.h"
#include "GameFramework/GameStateBase.h"
#include "XYZResourceType.h"
#include "XYZGameState.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AXYZGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void AddActorServer(class AXYZActor* Actor);
	UFUNCTION()
	void AddActorClient(class AXYZActor* Actor, int32 ActorUId);
	
	UFUNCTION()
	void LoadGameState();
	UPROPERTY()
	bool bLoadedGameState;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, class AXYZActor*> ActorsByUID;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> MineralsByTeamId = { 0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> GasByTeamId = { 0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> SupplyByTeamId = { 0,0,0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bHasGameEnded;
	
	TMap<int32,TMap<int32, int32>> ReservedSupplyByBuilding;
	UFUNCTION()
	TArray<class AXYZActor*> GetAllActors();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	int32 ActorIndex;

	bool bLinkedActors = false;
	bool bClientLoaded;

	UPROPERTY(BlueprintReadOnly, Replicated)
	EXYZMatchState MatchState = EXYZMatchState::WAITING_FOR_PLAYERS;

	UPROPERTY(BlueprintReadOnly, Replicated)
	float GameTime;

	UFUNCTION()
	class AXYZActor* GetActorById(int32 ActorId);
	
	UFUNCTION()
	void ProgressMatchState()
	{
		switch(MatchState)
		{
		case EXYZMatchState::WAITING_FOR_PLAYERS:
			MatchState = EXYZMatchState::MATCH_STARTING;
			break;
		case EXYZMatchState::MATCH_STARTING:
			MatchState = EXYZMatchState::IN_PROGRESS;
			break;
		case EXYZMatchState::IN_PROGRESS:
			MatchState = EXYZMatchState::CLEANING_UP;
			break;
		case EXYZMatchState::CLEANING_UP:
			MatchState = EXYZMatchState::SHUTTING_DOWN;
			break;
		case EXYZMatchState::SHUTTING_DOWN:
			MatchState = EXYZMatchState::GAME_OVER;
			break;
		case EXYZMatchState::GAME_OVER:
			break;
		default: ;
		}
	}
};
