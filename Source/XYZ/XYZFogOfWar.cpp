#include "XYZFogOfWar.h"

#include "XYZGameState.h"
#include "XYZPlayerController.h"

AXYZFogOfWar::AXYZFogOfWar()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = .5f;
}

void AXYZFogOfWar::BeginPlay()
{
	Super::BeginPlay();

}

void AXYZFogOfWar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(GetLocalRole() != ROLE_Authority) return;
	TArray<AXYZActor*> Actors;
	TSet<FVector2D> NonRevealedCoords;
	if(GetWorld())
	{
		if(GetWorld()->GetGameState())
		{
			GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.GenerateValueArray(Actors);
		}
	}
	for (AXYZActor* Actor : Actors) {
		if (!Actor || Actor->TeamId != GetWorld()->GetFirstPlayerController<AXYZPlayerController>()->TeamId) continue;

		FVector2D ActorGridCoord = FVector2D(FMath::FloorToInt(Actor->GetActorLocation().X / 200), FMath::FloorToInt(Actor->GetActorLocation().Y / 200));
		
		int32 CellsToCheck = FMath::CeilToInt(Actor->VisionRange / 200);

		for (int32 X = -CellsToCheck; X <= CellsToCheck; ++X) {
			for (int32 Y = -CellsToCheck; Y <= CellsToCheck; ++Y) {
				FVector2D AdjacentCoord(ActorGridCoord.X + X, ActorGridCoord.Y + Y);
				if(!RevealCoords.Contains(AdjacentCoord))
				{
					NonRevealedCoords.Add(AdjacentCoord);
					RevealCoords.Add(AdjacentCoord);
				}
			}
		}
	}

	for(FVector2D RevealCoord : NonRevealedCoords)
	{
		RevealCell(RevealCoord);
	}
	
}

void AXYZFogOfWar::RevealCell(FVector2D Coord)
{
	OnRevealCell.Broadcast(Coord);
}

void AXYZFogOfWar::ConcealCell(FVector2D Coord)
{
	OnConcealCell.Broadcast(Coord);
}
