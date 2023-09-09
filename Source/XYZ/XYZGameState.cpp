// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZGameState.h"
#include "EngineUtils.h"
#include "XYZActor.h"
#include "UObject/ConstructorHelpers.h"

void AXYZGameState::BeginPlay() {
	Super::BeginPlay();
	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (GetLocalRole() == ROLE_Authority) {
			AXYZActor* Actor = *ActorItr;
			AllActors.Add(Actor);
			ActorsByUID.Add(Actor->UActorId, Actor);
		}
		else {
			AXYZActor* Actor = *ActorItr;
			AllActors.Add(Actor);
			ActorsByUID.Add(Actor->UActorId, Actor);
		}
		
	}
}