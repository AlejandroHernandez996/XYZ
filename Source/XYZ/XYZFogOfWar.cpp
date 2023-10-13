#include "XYZFogOfWar.h"

#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

AXYZFogOfWar::AXYZFogOfWar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXYZFogOfWar::BeginPlay()
{
	Super::BeginPlay();
}

void AXYZFogOfWar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(CellsToUpdate.IsEmpty()) return;

	TArray<TArray<FIntVector2>> UpdateCells;
	CellsToUpdate.Dequeue(UpdateCells);

	for(FIntVector2 Coord : UpdateCells[0])
	{
		OnRevealCell.Broadcast(FVector2D(Coord.X, Coord.Y));
	}
	for(FIntVector2 Coord : UpdateCells[1])
	{
		OnConcealCell.Broadcast(FVector2D(Coord.X, Coord.Y));
	}

}

void AXYZFogOfWar::SetPlayerController(AXYZPlayerController* PlayerController)
{
	OwningController = PlayerController;
}

void AXYZFogOfWar::Update(const TArray<FIntVector2> Visible, const TArray<FIntVector2> NonVisible)
{
	CellsToUpdate.Enqueue({Visible, NonVisible});
}
