// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZGameState.h"
#include "EngineUtils.h"
#include "XYZActor.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"

AXYZGameState::AXYZGameState() {
	PrimaryActorTick.bCanEverTick = true;
}
void AXYZGameState::BeginPlay() {
	Super::BeginPlay();
}
void AXYZGameState::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bClientLoaded && ROLE_Authority == GetLocalRole() && !bLinkedActors) {
		for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AXYZActor* Actor = *ActorItr;
			ActorIndex++;
			Actor->UActorId = ActorIndex;
		}
		bLinkedActors = true;
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