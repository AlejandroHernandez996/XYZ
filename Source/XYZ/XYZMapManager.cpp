#include "XYZMapManager.h"
#include "GridCell.h"
#include "XYZActor.h"
#include "XYZGameState.h"

void UXYZMapManager::InitializeGrid() {
	for (int32 X = 0; X < GRID_SIZE; X++) {
		for (int32 Y = 0; Y < GRID_SIZE; Y++) {
			FVector2D GridCoord(X, Y);
			TSharedPtr<FGridCell> NewCell = MakeShared<FGridCell>();
			
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
		Grid[GridCoord]->ActorsInCell.Add(Actor);
	}
}

void UXYZMapManager::RemoveActorFromGrid(AXYZActor* Actor) {
	FVector2D GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	if(IsGridCoordValid(GridCoord))
	{
		Grid[GridCoord]->ActorsInCell.Remove(Actor);
	}
}

void UXYZMapManager::Process(float DeltaSeconds) {

	double StartTime = FPlatformTime::Cycles();
	if(bHasProcessed)
	{
		ClearVision();
		for(AXYZActor* Actor : ActorsToUpdate)
		{
			RemoveActorFromGrid(Actor);
			AddActorToGrid(Actor);
		}
		GenerateVision();
		ActorsToUpdate.Empty();
	}else
	{
		TArray<AXYZActor*> Actors;
		GameState->ActorsByUID.GenerateValueArray(Actors);
		for(AXYZActor* Actor : Actors)
		{
			AddActorToGrid(Actor);
		}
		GenerateVision();
		bHasProcessed = true;
	}
	double EndTime = FPlatformTime::Cycles();
	float ElapsedTime = FPlatformTime::ToSeconds(EndTime - StartTime);

	UE_LOG(LogTemp, Warning, TEXT("Process function took %f seconds"), ElapsedTime);
	
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
				ActorsInRange = ActorsInRange.Union(Grid[AdjacentCoord]->ActorsInCell);
			}
		}
	}
	return ActorsInRange;
}

void UXYZMapManager::ClearVision()
{
	TArray<TSharedPtr<FGridCell>> Cells;
	Grid.GenerateValueArray(Cells);

	for(TSharedPtr<FGridCell> Cell : Cells)
	{
		if(Cell)
		{
			Cell->TeamVision = {false, false};
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
					Grid[AdjacentCoord]->TeamVision.Num() > Actor->TeamId &&
					Grid[ActorGridCoord]->Height >= Grid[AdjacentCoord]->Height) {
					Grid[AdjacentCoord]->TeamVision[Actor->TeamId] = true;
				}
			}
		}
	}
}

bool UXYZMapManager::IsGridCoordValid(const FVector2D& Coord) const
{
	return Grid.Contains(Coord) && Grid[Coord];
}