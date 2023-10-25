#include "XYZMapManager.h"

#include "EngineUtils.h"
#include "GridCell.h"
#include "XYZActor.h"
#include "XYZBuilding.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "XYZResourceActor.h"
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
			FIntVector2 GridCoord(X, Y);
			TSharedPtr<FGridCell> NewCell = MakeShared<FGridCell>();

			FVector WorldCoord((GridCoord.X + 0.5f) * GridCellSize, (GridCoord.Y + 0.5f) * GridCellSize, 0);

			FVector Start = WorldCoord + FVector(0, 0, 1000);
			FVector End = WorldCoord;

			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActors(ActorsToIgnore);
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams);

			if (bHit) {
				NewCell->Height = HitResult.ImpactPoint.Z;
			}

			Grid.Add(GridCoord, NewCell);
		}
	}
}

FIntVector2 UXYZMapManager::GetGridCoordinate(const FVector& WorldLocation) {
	int32 x = FMath::FloorToInt(WorldLocation.X / GridCellSize);
	int32 y = FMath::FloorToInt(WorldLocation.Y / GridCellSize);

	x = FMath::Clamp(x, 0, GRID_SIZE - 1);
	y = FMath::Clamp(y, 0, GRID_SIZE - 1);

	return FIntVector2(x, y);
}

void UXYZMapManager::Process(float DeltaSeconds) {
	for(AXYZActor* Actor : ActorsToUpdate)
	{
		if(!Actor || Actor->IsA(AXYZResourceActor::StaticClass()))
		{
			continue;
		}
		RemoveActorFromGrid(Actor);
		AddActorToGrid(Actor);
	}
	
	SendDeltaVisibilityToClients();
	ActorsToUpdate.Empty();
	bHasSentVison = true;
}

void UXYZMapManager::AddToUpdateSet(AXYZActor* Actor)
{
	ActorsToUpdate.Add(Actor);
}

TArray<FIntVector2> UXYZMapManager::GetPerimeterCoords(FIntVector2 CenterGridCoord, FIntVector2 GridArea)
{
	TArray<FIntVector2> PerimeterCoords;
    
	int32 HalfSizeX = GridArea.X / 2;
	int32 HalfSizeY = GridArea.Y / 2;
	int32 MinX = CenterGridCoord.X - HalfSizeX;
	int32 MaxX = CenterGridCoord.X + HalfSizeX;
	int32 MinY = CenterGridCoord.Y - HalfSizeY;
	int32 MaxY = CenterGridCoord.Y + HalfSizeY;

	if(GridArea.X % 2 == 0) 
	{
		MaxX -= 1;
	}
	if(GridArea.Y % 2 == 0) 
	{
		MaxY -= 1;
	}

	for (int32 X = MinX; X <= MaxX; ++X)
	{
		PerimeterCoords.Add(FIntVector2(X, MinY - 1)); // Top edge
		PerimeterCoords.Add(FIntVector2(X, MaxY + 1)); // Bottom edge
	}

	for (int32 Y = MinY; Y <= MaxY; ++Y)
	{
		PerimeterCoords.Add(FIntVector2(MinX - 1, Y)); // Left edge
		PerimeterCoords.Add(FIntVector2(MaxX + 1, Y)); // Right edge
	}

	return PerimeterCoords;
}

bool UXYZMapManager::AreGridCoordsSameHeight(FIntVector2 Coord, FIntVector2 OtherCoord)
{
	return Grid.Contains(Coord) && Grid.Contains(OtherCoord) && Grid[Coord]->Height == Grid[OtherCoord]->Height;
}

bool UXYZMapManager::IsCoordOccupiedByBuilding(FIntVector2 Coord, int32 RangeOfCoordsToSearch)
{
	int32 MinX = Coord.X - RangeOfCoordsToSearch;
	int32 MaxX = Coord.X + RangeOfCoordsToSearch;
	int32 MinY = Coord.Y - RangeOfCoordsToSearch;
	int32 MaxY = Coord.Y + RangeOfCoordsToSearch;

	for (int32 X = MinX; X <= MaxX; ++X)
	{
		for (int32 Y = MinY; Y <= MaxY; ++Y)
		{
			FIntVector2 CurrentCoord(X, Y);

			if (Grid.Contains(CurrentCoord))
			{
				TSharedPtr<FGridCell> Cell = Grid[CurrentCoord];

				for (AXYZActor* Actor : Cell->ActorsInCell)
				{
					AXYZBuilding* Building = Cast<AXYZBuilding>(Actor);

					if(Building && Building->State != EXYZUnitState::DEAD)
					{
						FIntVector2 BuildingGridCoord = Building->GridCoord; 
						FIntVector2 BuildingGridSize = FIntVector2(Building->GridSize.X, Building->GridSize.Y);

						int32 HalfSizeX = BuildingGridSize.X / 2;
						int32 HalfSizeY = BuildingGridSize.Y / 2;
						int32 BuildingMinX = BuildingGridCoord.X - HalfSizeX;
						int32 BuildingMaxX = BuildingGridCoord.X + HalfSizeX;
						int32 BuildingMinY = BuildingGridCoord.Y - HalfSizeY;
						int32 BuildingMaxY = BuildingGridCoord.Y + HalfSizeY;

						if(BuildingGridSize.X % 2 == 0) --BuildingMaxX;
						if(BuildingGridSize.Y % 2 == 0) --BuildingMaxY;

						if (Coord.X >= BuildingMinX && Coord.X <= BuildingMaxX && Coord.Y >= BuildingMinY && Coord.Y <= BuildingMaxY)
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

FVector UXYZMapManager::GridCoordToWorldCoord(FIntVector2 Coord)
{
	if(Grid.Contains(Coord))
	{
		return FVector(
			(Coord.X * GridCellSize) + (GridCellSize * 0.5f), 
			(Coord.Y * GridCellSize) + (GridCellSize * 0.5f), 
			Grid[Coord]->Height
		);
	}
	return FVector::ZeroVector;
}

TSet<AXYZActor*> UXYZMapManager::FindActorsInRange(const FIntVector2& CenterGrid, float Radius)
{
	int32 CellsToCheck = FMath::CeilToInt(Radius / GridCellSize)+1;
	TSet<AXYZActor*> ActorsInRange;
	
	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) 
	{
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) 
		{
			FIntVector2 AdjacentCoord(CenterGrid.X + X, CenterGrid.Y + Y);
			if(!IsGridCoordValid(AdjacentCoord)) continue;
			ActorsInRange = ActorsInRange.Union(Grid[AdjacentCoord]->ActorsInCell);
		}
	}
	return ActorsInRange;
}

TSet<AXYZActor*> UXYZMapManager::FindActorsInVisionRange(AXYZActor* Actor)
{
	if(!Actor) return {};
	FIntVector2 GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize)+1;
	
	TSet<AXYZActor*> ActorsInRange;
	
	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) 
	{
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) 
		{
			FIntVector2 AdjacentCoord(GridCoord.X + X, GridCoord.Y + Y);
            
			if(IsGridCoordValid(AdjacentCoord) && TeamHasVision(Actor->TeamId, AdjacentCoord))
			{
				ActorsInRange = ActorsInRange.Union(Grid[AdjacentCoord]->ActorsInCell);
			}
		}
	}
	return ActorsInRange;
}

void UXYZMapManager::AddActorToGrid(AXYZActor* Actor) {
	if(!Actor) return;
	FIntVector2 GridCoord = GetGridCoordinate(Actor->GetActorLocation());
	if(IsGridCoordValid(GridCoord))
	{
		Grid[GridCoord]->ActorsInCell.Add(Actor);
		Actor->GridCoord = GridCoord;
		AddVisionForActor(Actor);
		for(int i = 0;i < 2;i++)
		{
			if(TeamHasVision(i, Actor->GridCoord))
			{
				VisibleActors[i].Add(Actor);
				NonVisibleActors[i].Remove(Actor);
			}
		}
	}
}

void UXYZMapManager::AddVisionForActor(AXYZActor* Actor)
{
	if (!Actor) return;

	FIntVector2 ActorGridCoord = GetGridCoordinate(Actor->GetActorLocation());
	if (!IsGridCoordValid(ActorGridCoord))
	{
		return;
	}
	/*int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize);

	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) {
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) {
			FIntVector2 AdjacentCoord(ActorGridCoord.X + X, ActorGridCoord.Y + Y);
			if(!IsGridCoordValid(AdjacentCoord) || Actor->TeamId == 2) continue;
			bool bIsHighGround = Grid[ActorGridCoord]->Height > Grid[AdjacentCoord]->Height;
			bool bIsCloseInHeight = FMath::Abs(Grid[ActorGridCoord]->Height - Grid[AdjacentCoord]->Height) < 50.0f;
			bool bCanSeeHeight = bIsHighGround || bIsCloseInHeight;
			if (Actor->bIsFlying || bCanSeeHeight) {
				AddActorVision(Actor, AdjacentCoord);
				VisibleCells[Actor->TeamId].Add(AdjacentCoord);
				NonVisibleCells[Actor->TeamId].Remove(AdjacentCoord);
			}
		}
	}
	*/
	int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize);
	int32 RadiusSquared = CellsToCheck * CellsToCheck; 

	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) {
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) {
			FIntVector2 AdjacentCoord(ActorGridCoord.X + X, ActorGridCoord.Y + Y);

			int32 DistanceSquared = (X * X) + (Y * Y);

			if (DistanceSquared <= RadiusSquared) {
				if (!IsGridCoordValid(AdjacentCoord) || Actor->TeamId == 2) continue;

				bool bIsHighGround = Grid[ActorGridCoord]->Height > Grid[AdjacentCoord]->Height;
				bool bIsCloseInHeight = FMath::Abs(Grid[ActorGridCoord]->Height - Grid[AdjacentCoord]->Height) < 50.0f;
				bool bCanSeeHeight = bIsHighGround || bIsCloseInHeight;

				if (Actor->bIsFlying || bCanSeeHeight) {
					AddActorVision(Actor, AdjacentCoord);
					VisibleCells[Actor->TeamId].Add(AdjacentCoord);
					NonVisibleCells[Actor->TeamId].Remove(AdjacentCoord);
				}
			}
		}
	}
}


void UXYZMapManager::AddActorVision(AXYZActor* Actor, FIntVector2 GridCoord)
{
	if(Actor && Grid[GridCoord]->ActorsWithVisionByTeam.IsValidIndex(Actor->TeamId))
	{
		Grid[GridCoord]->ActorsWithVisionByTeam[Actor->TeamId].Add(Actor);
		if(Actor->bHasTrueVision)
		{
			Grid[GridCoord]->ActorsWithTrueVisionByTeam[Actor->TeamId].Add(Actor);
		}
	}
}

void UXYZMapManager::RemoveVisionForActor(AXYZActor* Actor)
{
	if (!Actor) return;

	FIntVector2 ActorGridCoord = Actor->GridCoord;
	if (!IsGridCoordValid(ActorGridCoord))
	{
		return;
	}
	/*int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize);

	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) {
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) {
			FIntVector2 AdjacentCoord(ActorGridCoord.X + X, ActorGridCoord.Y + Y);
			if(!IsGridCoordValid(AdjacentCoord) || Actor->TeamId == 2) continue;
			bool bIsHighGround = Grid[ActorGridCoord]->Height > Grid[AdjacentCoord]->Height;
			bool bIsCloseInHeight = FMath::Abs(Grid[ActorGridCoord]->Height - Grid[AdjacentCoord]->Height) < 50.0f;
			bool bCanSeeHeight = bIsHighGround || bIsCloseInHeight;
			if (Actor->bIsFlying || bCanSeeHeight) {
				RemoveActorVision(Actor, AdjacentCoord);
				if(!TeamHasVision(Actor->TeamId, AdjacentCoord))
				{
					VisibleCells[Actor->TeamId].Remove(AdjacentCoord);
					NonVisibleCells[Actor->TeamId].Add(AdjacentCoord);
				}
			}
		}
	}
	*/
	int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / GridCellSize);
	int32 RadiusSquared = CellsToCheck * CellsToCheck; 

	for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) {
		for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) {
			FIntVector2 AdjacentCoord(ActorGridCoord.X + X, ActorGridCoord.Y + Y);
			int32 DistanceSquared = (X * X) + (Y * Y);
			if (DistanceSquared <= RadiusSquared) {
				if (!IsGridCoordValid(AdjacentCoord) || Actor->TeamId == 2) continue;
				bool bIsHighGround = Grid[ActorGridCoord]->Height > Grid[AdjacentCoord]->Height;
				bool bIsCloseInHeight = FMath::Abs(Grid[ActorGridCoord]->Height - Grid[AdjacentCoord]->Height) < 50.0f;
				bool bCanSeeHeight = bIsHighGround || bIsCloseInHeight;
				if (Actor->bIsFlying || bCanSeeHeight) {
					RemoveActorVision(Actor, AdjacentCoord);
					if(!TeamHasVision(Actor->TeamId, AdjacentCoord))
					{
						VisibleCells[Actor->TeamId].Remove(AdjacentCoord);
						NonVisibleCells[Actor->TeamId].Add(AdjacentCoord);
					}
				}
			}
		}
	}
}

void UXYZMapManager::RemoveActorFromGrid(AXYZActor* Actor) {
	if(Actor && IsGridCoordValid(Actor->GridCoord) && Grid[Actor->GridCoord]->ActorsInCell.Contains(Actor))
	{
		RemoveVisionForActor(Actor);
		Grid[Actor->GridCoord]->ActorsInCell.Remove(Actor);
		for(int i = 0;i < 2;i++)
		{
			if(!TeamHasVision(i, Actor->GridCoord))
			{
				NonVisibleActors[i].Add(Actor);
				VisibleActors[i].Remove(Actor);
			}
		}
	}
}

void UXYZMapManager::RemoveActorVision(AXYZActor* Actor, FIntVector2 GridCoord)
{
	if(Actor && Grid[GridCoord]->ActorsWithVisionByTeam.IsValidIndex(Actor->TeamId))
	{
		Grid[GridCoord]->ActorsWithVisionByTeam[Actor->TeamId].Remove(Actor);
		Grid[GridCoord]->ActorsWithTrueVisionByTeam[Actor->TeamId].Remove(Actor);
	}
}

bool UXYZMapManager::TeamHasVision(int32 TeamId, FIntVector2 GridCoord)
{
	if(Grid[GridCoord]->ActorsWithVisionByTeam.IsValidIndex(TeamId))
	{
		return Grid[GridCoord]->ActorsWithVisionByTeam[TeamId].Num() > 0;
	}
	return false;
}

bool UXYZMapManager::TeamHasTrueVision(int32 TeamId, FIntVector2 GridCoord)
{
	if(Grid[GridCoord]->ActorsWithTrueVisionByTeam.IsValidIndex(TeamId))
	{
		return Grid[GridCoord]->ActorsWithTrueVisionByTeam[TeamId].Num() > 0;
	}
	return false;
}

bool UXYZMapManager::IsGridCoordValid(const FIntVector2& Coord) const
{
	return Grid.Contains(Coord);
}

void UXYZMapManager::SendDeltaVisibilityToClients()
{
	for(AXYZPlayerController* PlayerController : GameMode->PlayerControllers)
	{
		int32 TeamId = PlayerController->TeamId;

		TSet<AXYZActor*> VisibleActorsDifference = VisibleActors[TeamId].Difference(LastVisibleActorsSent[TeamId]);
		TSet<AXYZActor*> NonVisibleActorsDifference = NonVisibleActors[TeamId].Difference(LastNonVisibleActorsSent[TeamId]);

		TSet<FIntVector2> VisibleCellsDifference = VisibleCells[TeamId].Difference(LastVisibleCellsSent[TeamId]);
		TSet<FIntVector2> NonVisibleCellsDifference = NonVisibleCells[TeamId].Difference(LastNonVisibleCellsSent[TeamId]);

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

bool UXYZMapManager::AreSets2DEqual(const TSet<FIntVector2>& SetA, const TSet<FIntVector2>& SetB)
{
	if (SetA.Num() != SetB.Num())
	{
		return false;
	}

	for (const FIntVector2& Element : SetA)
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

	if(!Actor ||
		!OtherActor ||
		!Grid.Contains(OtherActor->GridCoord) ||
		!TeamHasVision(Actor->TeamId, OtherActor->GridCoord))
	{
		return false;
	}

	return TeamHasVision(Actor->TeamId,OtherActor->GridCoord);
}

bool UXYZMapManager::DoesBuildingAreaOverlap(FIntVector2 CenterGridCoord, FIntVector2 GridAreaSize)
{
	int32 HalfSizeX = GridAreaSize.X / 2;
	int32 HalfSizeY = GridAreaSize.Y / 2;

	int32 MinX = CenterGridCoord.X - HalfSizeX;
	int32 MaxX = CenterGridCoord.X + HalfSizeX;
	int32 MinY = CenterGridCoord.Y - HalfSizeY;
	int32 MaxY = CenterGridCoord.Y + HalfSizeY;

	if(GridAreaSize.X % 2 == 0) --MaxX;
	if(GridAreaSize.Y % 2 == 0) --MaxY;

	for (int32 X = MinX; X <= MaxX; ++X)
	{
		for (int32 Y = MinY; Y <= MaxY; ++Y)
		{
			FIntVector2 CurrentCoord(X, Y);
			if (IsCoordOccupiedByBuilding(CurrentCoord))
			{
				return true;
			}
		}
	}

	return false;
}