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
	AXYZGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void AddActorServer(class AXYZActor* Actor);
	UFUNCTION()
	void AddActorClient(class AXYZActor* Actor, int32 ActorUId);
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, class AXYZActor*> ActorsByUID;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> MineralsByTeamId = { 2000,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> GasByTeamId = { 0,0 };
	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<int32> SupplyByTeamId = { 0,0,0,0 };
	TMap<int32,TMap<int32, int32>> ReservedSupplyByBuilding;
	UFUNCTION()
	TArray<class AXYZActor*> GetAllActors();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	int32 ActorIndex;

	bool bLinkedActors = false;
	bool bClientLoaded;
};
