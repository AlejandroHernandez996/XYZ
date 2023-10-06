﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "GridCell.h"
#include "XYZMapManager.generated.h"

UCLASS()
class XYZ_API UXYZMapManager : public UObject, public IProcessable
{
	GENERATED_BODY()
public:
	void Process(float DeltaSeconds) override;

	UFUNCTION()
	void AddToUpdateSet(AXYZActor* Actor);

	UPROPERTY()
	TMap<FVector2D, FGridCell> Grid;
	
	UPROPERTY()
	int32 GRID_SIZE = 100;
	UPROPERTY()
	float MAP_SIZE = 10000.0f;
	UPROPERTY()
	float GridCellSize;
	
	UPROPERTY()
	TSet<class AXYZActor*> ActorsToUpdate;
	UPROPERTY()
	bool bHasProcessed;
	UPROPERTY()
	class AXYZGameState* GameState;
	UPROPERTY()
	class AXYZGameMode* GameMode;
	
	void InitializeGrid();
	UFUNCTION()
	FVector2D GetGridCoordinate(const FVector& WorldLocation);
	UFUNCTION()
	void AddActorToGrid(class AXYZActor* Actor);
	UFUNCTION()
	void RemoveActorFromGrid(class AXYZActor* Actor);
	UFUNCTION()
	TSet<AXYZActor*> FindActorsInVisionRange(AXYZActor* Actor);
	UFUNCTION()
	void ClearVision();
	UFUNCTION()
	void GenerateVision();
	UFUNCTION()
	bool IsGridCoordValid(const FVector2D& Coord) const;

	UFUNCTION()
	void SendDeltaVisibilityToClients();

	TArray<TSet<int32>> LastVisibleSent = {{},{}};
	TArray<TSet<int32>> LastNonVisibleSent = {{},{}};
	TArray<TSet<AXYZActor*>> LastVisibleActorsSent = {{},{}};
	TArray<TSet<AXYZActor*>> LastNonVisibleActorsSent = {{},{}};
	TArray<TSet<FVector2D>> LastVisibleCellsSent = {{},{}};
	TArray<TSet<FVector2D>> LastNonVisibleCellsSent = {{},{}};

	UFUNCTION()
	bool AreSetsEqual(const TSet<int32>& SetA, const TSet<int32>& SetB);
	UFUNCTION()
	bool AreSets2DEqual(const TSet<FVector2D>& SetA, const TSet<FVector2D>& SetB);
	UFUNCTION()
	bool DoesActorHasVisionOfActor(AXYZActor* Actor, AXYZActor* OtherActor);
	UFUNCTION()
	TArray<int32> ConvertSetToActorIds(const TSet<AXYZActor*>& ActorSet);

	bool bHasSentVison;

	float TimeToSendGrid = 1.0f;
	float TimeSinceSent = 0.0f;
};

