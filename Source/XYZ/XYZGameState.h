// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "XYZResourceType.h"
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
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, class AXYZActor*> ActorsByUID;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> MineralsByTeamId = { 0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> GasByTeamId = { 0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> SupplyByTeamId = { 0,0,0,0 };
	UFUNCTION()
	TArray<class AXYZActor*> GetAllActors();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	int32 ActorIndex;
};
