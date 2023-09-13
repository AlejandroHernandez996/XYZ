// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZGameState.h"
#include "EngineUtils.h"
#include "XYZActor.h"
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

TArray<class AXYZActor*> AXYZGameState::GetAllActors() {
	TArray< AXYZActor*> AllActors;
	ActorsByUID.GenerateValueArray(AllActors);
	return AllActors;
}