#include "XYZFogOfWar.h"

#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

AXYZFogOfWar::AXYZFogOfWar()
{
	//PrimaryActorTick.TickInterval = .5f;
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

	TArray<TArray<FVector2D>> UpdateCells;
	CellsToUpdate.Dequeue(UpdateCells);

	for(FVector2D Coord : UpdateCells[0])
	{
		OnRevealCell.Broadcast(Coord);
	}
	for(FVector2D Coord : UpdateCells[1])
	{
		OnConcealCell.Broadcast(Coord);
	}

}

void AXYZFogOfWar::RevealCell(FVector2D Coord)
{
}

void AXYZFogOfWar::ConcealCell(FVector2D Coord)
{
}

void AXYZFogOfWar::SetPlayerController(AXYZPlayerController* PlayerController)
{
	OwningController = PlayerController;
}

void AXYZFogOfWar::Update(const TArray<FVector2D> Visible, const TArray<FVector2D> NonVisible)
{
	CellsToUpdate.Enqueue({Visible, NonVisible});
}
