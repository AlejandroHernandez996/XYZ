#include "XYZMapManager.h"

#include "EngineUtils.h"
#include "GridCell.h"
#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "Misc/FileHelper.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void UXYZMapManager::InitializeGrid() {
	Grid.Empty();
	GridCellSize = MAP_SIZE / GRID_SIZE; 

	TArray<AActor*> ActorsToIgnore;
	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		ActorsToIgnore.Add(*ActorItr);
	}
	
	for (int32 X = 0; X < GRID_SIZE; X++) {
		for (int32 Y = 0; Y < GRID_SIZE; Y++) {
			FVector2D GridCoord(X, Y);
			FGridCell NewCell;

			FVector WorldCoord((GridCoord.X + 0.5f) * GridCellSize, (GridCoord.Y + 0.5f) * GridCellSize, 0);

			FVector Start = WorldCoord + FVector(0, 0, 1000);
			FVector End = WorldCoord;

			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActors(ActorsToIgnore);
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams);

			if (bHit) {
				NewCell.Height = HitResult.ImpactPoint.Z;
			}

			Grid.Add(GridCoord, NewCell);
		}
	}
}

FVector2D UXYZMapManager::GetGridCoordinate(const FVector& WorldLocation) {
	return FVector2D(FMath::FloorToInt(WorldLocation.X / GridCellSize), FMath::FloorToInt(WorldLocation.Y / GridCellSize));
}

void UXYZMapManager::AddActorToGrid(AXYZActor* Actor) {
	if(!Actor) return;
	FVector2D GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	if(IsGridCoordValid(GridCoord))
	{
		Grid[GridCoord].ActorsInCell.Add(Actor);
		Actor->GridCoord = GridCoord;
	}
}

void UXYZMapManager::RemoveActorFromGrid(AXYZActor* Actor) {
	if(Actor && IsGridCoordValid(Actor->GridCoord) && Grid[Actor->GridCoord].ActorsInCell.Contains(Actor))
	{
		Grid[Actor->GridCoord].ActorsInCell.Remove(Actor);
	}
}

void UXYZMapManager::Process(float DeltaSeconds) {
	if(bHasSentVison)
	{
		ClearVision();
		for(AXYZActor* Actor : ActorsToUpdate)
		{
			RemoveActorFromGrid(Actor);
			AddActorToGrid(Actor);
		}
	}else
	{
		TArray<AXYZActor*> Actors;
		GameState->ActorsByUID.GenerateValueArray(Actors);
		for(AXYZActor* Actor : Actors)
		{
			AddActorToGrid(Actor);
		}
	}
	GenerateVision();
	SendDeltaVisibilityToClients();
	bHasSentVison = true;
}

void UXYZMapManager::AddToUpdateSet(AXYZActor* Actor)
{
	ActorsToUpdate.Add(Actor);
}

TSet<AXYZActor*> UXYZMapManager::FindActorsInVisionRange(AXYZActor* Actor)
{
	if(!Actor) return {};
	FVector2D GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize)+1;
	
	TSet<AXYZActor*> ActorsInRange;
	
	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) 
	{
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) 
		{
			FVector2D AdjacentCoord(GridCoord.X + X, GridCoord.Y + Y);
            
			if(IsGridCoordValid(GridCoord) && IsGridCoordValid(AdjacentCoord) && Grid[Actor->GridCoord].Height >= Grid[AdjacentCoord].Height)
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

void UXYZMapManager::SendDeltaVisibilityToClients()
{
	TArray<TSet<FVector2D>> VisibleCells = {{},{}};
	TArray<TSet<FVector2D>> NonVisibleCells = {{},{}};
	
	TArray<TSet<AXYZActor*>> VisibleActors = {{},{}};
	TArray<TSet<AXYZActor*>> NonVisibleActors = {{},{}};

	for (const TPair<FVector2D, FGridCell>& KVP : Grid)
	{
		FGridCell Cell = KVP.Value;
		FVector2d Coord = KVP.Key;
		for(AXYZPlayerController* PlayerController : GameMode->PlayerControllers)
		{
			int32 TeamId = PlayerController->TeamId;
			if(Cell.TeamVision[TeamId])
			{
				VisibleActors[TeamId] = Cell.ActorsInCell.Union(VisibleActors[TeamId]);
				VisibleCells[TeamId].Add(Coord);
			}else
			{
				NonVisibleActors[TeamId] = Cell.ActorsInCell.Union(NonVisibleActors[TeamId]);
				NonVisibleCells[TeamId].Add(Coord);
			}
		}
	}
	
	for(AXYZPlayerController* PlayerController : GameMode->PlayerControllers)
	{
		int32 TeamId = PlayerController->TeamId;

		TSet<AXYZActor*> VisibleActorsDifference = VisibleActors[TeamId].Difference(LastVisibleActorsSent[TeamId]);
		TSet<AXYZActor*> NonVisibleActorsDifference = NonVisibleActors[TeamId].Difference(LastNonVisibleActorsSent[TeamId]);

		TSet<FVector2D> VisibleCellsDifference = VisibleCells[TeamId].Difference(LastVisibleCellsSent[TeamId]);
		TSet<FVector2D> NonVisibleCellsDifference = NonVisibleCells[TeamId].Difference(LastNonVisibleCellsSent[TeamId]);

		bool bIsDifferent = !VisibleCellsDifference.IsEmpty() || !NonVisibleCellsDifference.IsEmpty() || !NonVisibleActorsDifference.IsEmpty() || !VisibleActorsDifference.IsEmpty();
		if(bIsDifferent)
		{
			if(bHasSentVison)
			{
				PlayerController->UpdateClientVisibility(ConvertSetToActorIds(VisibleActorsDifference),  ConvertSetToActorIds(NonVisibleActorsDifference), VisibleCellsDifference.Array(),  NonVisibleCellsDifference.Array());

			}else
			{
				PlayerController->UpdateClientVisibility(ConvertSetToActorIds(VisibleActorsDifference),  ConvertSetToActorIds(NonVisibleActorsDifference), VisibleCellsDifference.Array(),  {});
			}
		}
		
	}

	LastVisibleActorsSent = VisibleActors;
	LastNonVisibleActorsSent = NonVisibleActors;
	LastVisibleCellsSent = VisibleCells;
	LastNonVisibleCellsSent = NonVisibleCells;
}

TArray<int32> UXYZMapManager::ConvertSetToActorIds(const TSet<AXYZActor*>& ActorSet)
{
	TArray<int32> ActorIds;
	
	for (AXYZActor* Actor : ActorSet)
	{
		if (Actor)
			{
			ActorIds.Add(Actor->UActorId); 
			}
	}
	
	return ActorIds;
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

bool UXYZMapManager::DoesActorHasVisionOfActor(AXYZActor* Actor, AXYZActor* OtherActor)
{

	if(!Actor || !OtherActor || !Grid.Contains(Actor->GridCoord) || !Grid.Contains(OtherActor->GridCoord) || !(Actor->TeamId >= 0 && Actor->TeamId <= 1))
	{
		return false;
	}

	return Grid[OtherActor->GridCoord].TeamVision[Actor->TeamId];
}