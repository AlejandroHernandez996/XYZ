// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZGameState.h"
#include "EngineUtils.h"
#include "XYZActor.h"
#include "UObject/ConstructorHelpers.h"

void AXYZGameState::BeginPlay() {
	Super::BeginPlay();

	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AXYZActor* Actor = *ActorItr;
		// Do something with Actor, for example add it to an array
		AllActors.Add(Actor);
		ActorsByUID.Add(Actor->UActorId, Actor);
	}
}