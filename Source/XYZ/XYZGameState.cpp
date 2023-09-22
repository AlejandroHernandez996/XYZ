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

			if (Actor->TeamId == 0 || Actor->TeamId == 1) {
				SupplyByTeamId[Actor->TeamId] += Actor->SupplyCost;
				SupplyByTeamId[Actor->TeamId + 2] += Actor->SupplyGain;
			}
		}
		TMap<int32, int32> ReservedSupply1;
		TMap<int32, int32> ReservedSupply2;
		ReservedSupplyByBuilding.Add(0, ReservedSupply1);
		ReservedSupplyByBuilding.Add(1, ReservedSupply2);

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
	DOREPLIFETIME(AXYZGameState, SupplyByTeamId);
}