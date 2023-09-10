// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "XYZGameState.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<class AXYZActor*> AllActors;

	UPROPERTY(BlueprintReadOnly)
	TMap<int32, class AXYZActor*> ActorsByUID;

};
