#include "XYZMapManager.h"
#include "GridCell.h"
#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "Misc/FileHelper.h"

void UXYZMapManager::InitializeGrid() {
	Grid.Empty();
	for (int32 X = 0; X < GRID_SIZE; X++) {
		for (int32 Y = 0; Y < GRID_SIZE; Y++) {
			FVector2D GridCoord(X, Y);
			FGridCell NewCell;
			
			Grid.Add(GridCoord, NewCell);
		}
	}
	GridCellSize = MAP_SIZE/GRID_SIZE;
}

FVector2D UXYZMapManager::GetGridCoordinate(const FVector& WorldLocation) {
	return FVector2D(FMath::FloorToInt(WorldLocation.X / GridCellSize), FMath::FloorToInt(WorldLocation.Y / GridCellSize));
}

void UXYZMapManager::AddActorToGrid(AXYZActor* Actor) {
	FVector2D GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	if(IsGridCoordValid(GridCoord))
	{
		Grid[GridCoord].ActorsInCell.Add(Actor);
	}
}

void UXYZMapManager::RemoveActorFromGrid(AXYZActor* Actor) {
	FVector2D GridCoord = GetGridCoordinate(Actor->LastLocation);
	if(IsGridCoordValid(GridCoord))
	{
		Grid[GridCoord].ActorsInCell.Remove(Actor);
	}
}

void UXYZMapManager::Process(float DeltaSeconds) {

	TArray<AXYZActor*> Actors;
	GameState->ActorsByUID.GenerateValueArray(Actors);
	InitializeGrid();
	for(AXYZActor* Actor : Actors)
	{
		AddActorToGrid(Actor);
	}
	GenerateVision();
	SendVisibleActorsToClient();
	//SendVisibilityGrid();
	bHasSentVison = true;

}

void UXYZMapManager::AddToUpdateSet(AXYZActor* Actor)
{
	ActorsToUpdate.Add(Actor);
}

TSet<AXYZActor*> UXYZMapManager::FindActorsInVisionRange(AXYZActor* Actor)
{
	FVector2D GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize)+1;
	
	TSet<AXYZActor*> ActorsInRange;
	
	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) 
	{
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) 
		{
			FVector2D AdjacentCoord(GridCoord.X + X, GridCoord.Y + Y);
            
			if(IsGridCoordValid(GridCoord) && IsGridCoordValid(AdjacentCoord))
			{
				ActorsInRange = ActorsInRange.Union(Grid[AdjacentCoord].ActorsInCell);
			}
		}
	}
	return ActorsInRange;
}

void UXYZMapManager::ClearVision()
{
	for (int32 X = 0; X < GRID_SIZE; X++) {
		for (int32 Y = 0; Y < GRID_SIZE; Y++) {
			FVector2D GridCoord(X, Y);
			Grid[GridCoord].TeamVision = {false, false};
		}
	}
}

void UXYZMapManager::GenerateVision() {
	TArray<AXYZActor*> Actors;
	GameState->ActorsByUID.GenerateValueArray(Actors);

	for (AXYZActor* Actor : Actors) {
		if (!Actor) continue;

		FVector2D ActorGridCoord = GetGridCoordinate(Actor->GetActorLocation());
		if (!IsGridCoordValid(ActorGridCoord))
		{
			continue;
		}
		int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize);

		for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) {
			for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) {
				FVector2D AdjacentCoord(ActorGridCoord.X + X, ActorGridCoord.Y + Y);
				if (IsGridCoordValid(AdjacentCoord) &&
					Actor->TeamId != 2 &&
					Grid[ActorGridCoord].Height >= Grid[AdjacentCoord].Height) {
					Grid[AdjacentCoord].TeamVision[Actor->TeamId] = true;
				}
			}
		}
	}
}

bool UXYZMapManager::IsGridCoordValid(const FVector2D& Coord) const
{
	return Grid.Contains(Coord);
}

void UXYZMapManager::SendVisibleActorsToClient()
{
	
	TArray<FGridCell> GridCells;
	Grid.GenerateValueArray(GridCells);
	
	for(AXYZPlayerController* PlayerController : GameMode->PlayerControllers)
	{
		TSet<int32> VisibleActors;
		TSet<int32> NonVisibleActors;

		for(FGridCell Cell : GridCells)
		{
			if(Cell.ActorsInCell.IsEmpty()) continue;
			
			if(Cell.TeamVision[PlayerController->TeamId])
			{
				for(AXYZActor* Actor : Cell.ActorsInCell)
				{
					if(Actor && Actor->TeamId != PlayerController->TeamId && Actor->TeamId != 2)
					{
						VisibleActors.Add(Actor->UActorId);
					}
				}
			}else
			{
				for(AXYZActor* Actor : Cell.ActorsInCell)
				{
					if(Actor && Actor->TeamId != PlayerController->TeamId && Actor->TeamId != 2)
					{
						NonVisibleActors.Add(Actor->UActorId);
					}
				}
			}
		}
		bool bAreLastVisionSetsEqual = AreSetsEqual(LastVisibleSent[PlayerController->TeamId], VisibleActors);
		bool bAreLastNonVisionSetsEqual = AreSetsEqual(LastNonVisibleSent[PlayerController->TeamId], NonVisibleActors);
		bool bHasVisionChanged = !bAreLastVisionSetsEqual || !bAreLastNonVisionSetsEqual;
		if(!bHasSentVison || bHasVisionChanged)
		{
			PlayerController->SetVisibleEnemyActors(VisibleActors.Array(), NonVisibleActors.Array());
		}
		LastNonVisibleSent[PlayerController->TeamId] = NonVisibleActors;
		LastVisibleSent[PlayerController->TeamId] = VisibleActors;
	}
}

bool UXYZMapManager::AreSetsEqual(const TSet<int32>& SetA, const TSet<int32>& SetB)
{
	if (SetA.Num() != SetB.Num())
	{
		return false;
	}

	for (const int32& Element : SetA)
	{
		if (!SetB.Contains(Element))
		{
			return false;
		}
	}

	return true;
}

bool UXYZMapManager::AreSets2DEqual(const TSet<FVector2D>& SetA, const TSet<FVector2D>& SetB)
{
	if (SetA.Num() != SetB.Num())
	{
		return false;
	}

	for (const FVector2D& Element : SetA)
	{
		if (!SetB.Contains(Element))
		{
			return false;
		}
	}

	return true;
}

void UXYZMapManager::SendVisibilityGrid()
{
	TArray<TSet<FVector2D>> VisibleCells = {{},{}};
	TArray<TSet<FVector2D>> NonVisibleCells = {{},{}};

	for (const TPair<FVector2D, FGridCell>& KVP : Grid)
	{
		FVector2D Coord = KVP.Key;
		FGridCell Cell = KVP.Value;

		for(AXYZPlayerController* PlayerController : GameMode->PlayerControllers)
		{
			int32 TeamId = PlayerController->TeamId;
			if(Cell.TeamVision[TeamId])
			{
				VisibleCells[TeamId].Add(Coord);
			}else
			{
				NonVisibleCells[TeamId].Add(Coord);
			}
		}
	}
	
	for(AXYZPlayerController* PlayerController : GameMode->PlayerControllers)
	{
		int32 TeamId = PlayerController->TeamId;
		TSet<FVector2D> VisibleCellsIntersection = VisibleCells[TeamId].Intersect(LastNonVisibleCellsSent[TeamId]);
		TSet<FVector2D> NonVisibleCellsIntersection = NonVisibleCells[TeamId].Intersect(LastVisibleCellsSent[TeamId]);

		if(!VisibleCellsIntersection.IsEmpty() || !NonVisibleCellsIntersection.IsEmpty())
		{
			PlayerController->SendVisibilityGridCoords(VisibleCellsIntersection.Array(), NonVisibleCellsIntersection.Array());
		}

	}

	LastVisibleCellsSent = VisibleCells;
	LastNonVisibleCellsSent = NonVisibleCells;
	
}
