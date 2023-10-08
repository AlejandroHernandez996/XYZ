// Fill out your copyright notice in the Description page of Project Settings.
#include "XYZGameState.h"
#include "EngineUtils.h"
#include "XYZActor.h"
#include "Engine.h"
#include "XYZActorCache.h"
#include "XYZBuilding.h"
#include "XYZGameMode.h"
#include "XYZSoundManager.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

AXYZGameState::AXYZGameState() {
	PrimaryActorTick.bCanEverTick = true;
}
void AXYZGameState::BeginPlay() {
	Super::BeginPlay();
}
void AXYZGameState::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!SoundManager)
	{
		for (TActorIterator<AXYZSoundManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			SoundManager = *ActorItr;
		}
	}

	if(!HasAuthority() && SoundManager && MatchState == EXYZMatchState::IN_PROGRESS)
	{
		SoundManager->PlayBackgroundMusic();
	}
}

TArray<class AXYZActor*> AXYZGameState::GetAllActors() {
	TArray< AXYZActor*> AllActors;
	ActorsByUID.GenerateValueArray(AllActors);
	return AllActors;
}

void AXYZGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZGameState, GasByTeamId);
	DOREPLIFETIME(AXYZGameState, MineralsByTeamId);
	DOREPLIFETIME(AXYZGameState, SupplyByTeamId);
	DOREPLIFETIME(AXYZGameState, bHasGameEnded);
	DOREPLIFETIME(AXYZGameState, GameTime);
	DOREPLIFETIME(AXYZGameState, MatchState);
}

AXYZActor* AXYZGameState::GetActorById(int32 ActorId)
{
	TArray<AXYZActor*> Actors;
	ActorsByUID.GenerateValueArray(Actors);
	for(AXYZActor* Actor : Actors)
	{
		if(Actor && Actor->ActorId == ActorId)
		{
			return Actor;
		}
	}
	return nullptr;
}

void AXYZGameState::AddActorServer(AXYZActor* Actor)
{
	if(!ActorsByUID.Contains(Actor->UActorId))
	{
		UXYZActorCache* ActorCache = GetWorld()->GetAuthGameMode<AXYZGameMode>()->ActorCache;
		if(ActorCache && !Actor->IsA(AXYZBuilding::StaticClass()))
		{
			ActorCache->AddActorCount(Actor->TeamId, Actor->ActorId);
		}
		Actor->UActorId = ActorIndex;
		ActorsByUID.Add(ActorIndex, Actor);
		ActorIndex++;
	}
	
}

void AXYZGameState::AddActorClient(AXYZActor* Actor, int32 ActorUId)
{
	if(!ActorsByUID.Contains(ActorUId))
	{
		ActorsByUID.Add(ActorUId, Actor);
	}
}

void AXYZGameState::LoadGameState()
{
	if(bLoadedGameState || !HasAuthority()) return;

	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AXYZActor* Actor = *ActorItr;
		AddActorServer(Actor);

		if (Actor->TeamId == 0 || Actor->TeamId == 1) {
			SupplyByTeamId[Actor->TeamId] += Actor->SupplyCost;
			SupplyByTeamId[Actor->TeamId + 2] += Actor->SupplyGain;
		}
	}
	TMap<int32, int32> ReservedSupply1;
	TMap<int32, int32> ReservedSupply2;
	ReservedSupplyByBuilding.Add(0, ReservedSupply1);
	ReservedSupplyByBuilding.Add(1, ReservedSupply2);

	bLoadedGameState = true;
}    