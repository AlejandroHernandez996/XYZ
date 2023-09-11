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
		FString ActorName = Actor->GetName();
		int32 IndexOfLastDigit = 0;

		// Loop backwards to find the first non-numeric character
		for (int32 i = ActorName.Len() - 1; i >= 0; --i)
		{
			if (!FChar::IsDigit(ActorName[i]))
			{
				IndexOfLastDigit = i + 1;
				break;
			}
		}

		// Extract the numeric part and convert to int
		FString NumericPart = ActorName.Mid(IndexOfLastDigit);
		int32 NumericValue;
		if (NumericPart.IsNumeric())
		{
			NumericValue = FCString::Atoi(*NumericPart);
			Actor->UActorId = NumericValue;
			ActorsByUID.Add(NumericValue, Actor);
		}
	}
}

TArray<class AXYZActor*> AXYZGameState::GetAllActors() {
	TArray< AXYZActor*> AllActors;
	ActorsByUID.GenerateValueArray(AllActors);
	return AllActors;
}