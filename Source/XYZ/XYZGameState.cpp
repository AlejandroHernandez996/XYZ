// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZGameState.h"
#include "EngineUtils.h"
#include "XYZActor.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

void AXYZGameState::BeginPlay() {
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority) {
		for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AXYZActor* Actor = *ActorItr;
			Actor->UActorId = ActorIndex;
			ActorIndex++;
		}
	}
	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AXYZActor* Actor = *ActorItr;
		ActorsByUID.Add(Actor->UActorId, Actor);
	}
}
void AXYZGameState::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AXYZActor* Actor = *ActorItr;
		if (!ActorsByUID.Contains(Actor->UActorId)) {
			ActorsByUID.Add(Actor->UActorId, Actor);
		}
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
}