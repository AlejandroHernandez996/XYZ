// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeAbilitiesResearched.h"
#include "XYZMatchState.h"
#include "GameFramework/GameStateBase.h"
#include "XYZGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatMessageReceived, const FString&, ChatMessage);

UCLASS()
class XYZ_API AXYZGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AXYZGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class UXYZChatManager* ChatManager;
	UPROPERTY(Replicated)
	FString ChatLobbyId;
	UFUNCTION(BlueprintCallable)
	void SendMessage(FString Message, class AXYZPlayerController* PlayerController);
	UPROPERTY(BlueprintReadOnly)
	FString LobbyMessages;
	bool bStartGettingMessages = false;
	
	UPROPERTY(Replicated)
	TArray<FString> UsernamesByTeamId = {"", ""};
	
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
		TArray<int32> MineralsByTeamId = { 1000,1000 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> GasByTeamId = { 0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> SupplyByTeamId = { 0,0,0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bHasGameEnded;

	UPROPERTY(BlueprintReadOnly, Replicated)
	FUpgradeAbilitiesResearched UpgradeAbilitiesResearched;
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

	UFUNCTION(BlueprintCallable)
	FString GetFormattedGameTime()
	{
		int32 TotalSeconds = FMath::RoundToInt(GameTime);

		int32 Hours = TotalSeconds / 3600;
		TotalSeconds %= 3600;

		int32 Minutes = TotalSeconds / 60;
		TotalSeconds %= 60;

		int32 Seconds = TotalSeconds;

		return FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Minutes, Seconds);
	}
	
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

	UPROPERTY()
	class AXYZSoundManager* SoundManager;
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChatMessageReceived OnChatMessageReceivedEvent;

	UFUNCTION(BlueprintCallable)
	bool HasTeamFullyResearchedAbility(int32 TeamId, int32 AbilityId, int32 MaxStage);

	UFUNCTION(BlueprintCallable)
	bool DoesAbilityHaveRequirements(UXYZAbility* Ability, int32 TeamId);
};
