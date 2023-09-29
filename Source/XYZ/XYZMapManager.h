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

	TMap<FVector2D, TSharedPtr<FGridCell>> Grid;
	UPROPERTY()
	int32 GRID_SIZE = 50;
	UPROPERTY()
	float MAP_SIZE = 10000.0f;
	UPROPERTY()
	float GridCellSize;
	
	UPROPERTY()
	TSet<class AXYZActor*> ActorsToUpdate;
	UPROPERTY()
	bool bHasProcessed;

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
	UPROPERTY()
	class AXYZGameState* GameState;
};