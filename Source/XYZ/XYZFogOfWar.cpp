#include "XYZFogOfWar.h"

AXYZFogOfWar::AXYZFogOfWar()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AXYZFogOfWar::BeginPlay()
{
	Super::BeginPlay();

}

void AXYZFogOfWar::RevealCell(FVector2D Coord)
{
	OnRevealCell.Broadcast(Coord);
}

void AXYZFogOfWar::ConcealCell(FVector2D Coord)
{
	OnConcealCell.Broadcast(Coord);
}