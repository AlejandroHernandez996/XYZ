// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "GridCell.h"
#include "XYZTargetAreaAbility.h"
#include "XYZMapManager.generated.h"

UCLASS()
class XYZ_API UXYZMapManager : public UObject, public IProcessable
{
	GENERATED_BODY()
public:
	void Process(float DeltaSeconds) override;

	UFUNCTION()
	void AddToUpdateSet(AXYZActor* Actor);
	TArray<FIntVector2> GetPerimeterCoords(FIntVector2 CenterGridCoord, FIntVector2 GridArea);
	bool AreGridCoordsSameHeight(FIntVector2 Coord, FIntVector2 OtherCoord);
	bool IsCoordOccupiedByBuilding(FIntVector2 Coord, int32 RangeOfCoordsToSearch = 10);
	FVector GridCoordToWorldCoord(FIntVector2 Coord);

	TSet<AXYZActor*> FindActorsInRange(const FIntVector2& CenterGrid, float Radius);

	TMap<FIntVector2, TSharedPtr<FGridCell>> Grid;

	inline static int32 GRID_SIZE = 128;
	UPROPERTY()
	float MAP_SIZE = 10000;
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
	FIntVector2 GetGridCoordinate(const FVector& WorldLocation);
	UFUNCTION()
	void AddActorToGrid(class AXYZActor* Actor);
	UFUNCTION()
	void RemoveActorFromGrid(class AXYZActor* Actor);
	UFUNCTION()
	TSet<AXYZActor*> FindActorsInVisionRange(AXYZActor* Actor);
	UFUNCTION()
	void AddVisionForActor(AXYZActor* Actor);
	UFUNCTION()
	void RemoveVisionForActor(AXYZActor* Actor);
	UFUNCTION()
	bool IsGridCoordValid(const FIntVector2& Coord) const;

	UFUNCTION()
	void SendDeltaVisibilityToClients();

	TArray<TSet<int32>> LastVisibleSent = {{},{}};
	TArray<TSet<int32>> LastNonVisibleSent = {{},{}};
	TArray<TSet<AXYZActor*>> LastVisibleActorsSent = {{},{}};
	TArray<TSet<AXYZActor*>> LastNonVisibleActorsSent = {{},{}};
	TArray<TSet<FIntVector2>> LastVisibleCellsSent = {{},{}};
	TArray<TSet<FIntVector2>> LastNonVisibleCellsSent = {{},{}};

	TArray<TSet<FIntVector2>> VisibleCells = {{},{}};
	TArray<TSet<FIntVector2>> NonVisibleCells = {{},{}};
	TArray<TSet<AXYZActor*>> VisibleActors = {{},{}};
	TArray<TSet<AXYZActor*>> NonVisibleActors = {{},{}};
	
	UFUNCTION()
	bool AreSetsEqual(const TSet<int32>& SetA, const TSet<int32>& SetB);
	UFUNCTION()
	bool AreSets2DEqual(const TSet<FIntVector2>& SetA, const TSet<FIntVector2>& SetB);
	UFUNCTION()
	bool DoesActorHasVisionOfActor(AXYZActor* Actor, AXYZActor* OtherActor);
	bool DoesBuildingAreaOverlap(FIntVector2 CenterGridCoord, FIntVector2 GridAreaSize);
	UFUNCTION()
	TArray<int32> ConvertSetToActorIds(const TSet<AXYZActor*>& ActorSet);

	bool bHasSentVison;

	float TimeToSendGrid = 1.0f;
	float TimeSinceSent = 0.0f;

	void RemoveActorVision(AXYZActor* Actor, FIntVector2 GridCoord);

	void AddActorVision(AXYZActor* Actor, FIntVector2 GridCoord);

	bool TeamHasVision(int32 TeamId, FIntVector2 GridCoord);
};

