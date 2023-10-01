// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZMinimapManager.h"
#include "XYZActor.h"

// Sets default values
AXYZMinimapManager::AXYZMinimapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = .5f;
}

// Called when the game starts or when spawned
void AXYZMinimapManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXYZMinimapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FVector2D> UnitCoords;
	TArray<FColor> UnitColors;

	for(AXYZActor* VisibleActor : VisibleActors)
	{
		if(!VisibleActor) continue;
		UnitCoords.Add(FVector2D(MinimapSize-FMath::FloorToInt(VisibleActor->GetActorLocation().X / MinimapSize),
							MinimapSize-FMath::FloorToInt(VisibleActor->GetActorLocation().Y / MinimapSize)));
		if(VisibleActor->TeamId == TeamId)
		{
			UnitColors.Add(FColor::Green);
		}
		else if(VisibleActor->TeamId == 2)
		{
			UnitColors.Add(FColor::Yellow);
		}
		else
		{
			UnitColors.Add(FColor::Red);
		}
	}
	if(UnitCoords.IsEmpty()) return;
	OnClearMinimap.Broadcast(TeamId);
	OnUpdateMinimap.Broadcast(UnitCoords,UnitColors,TeamId);
}

void AXYZMinimapManager::UpdateVisibleActors(TSet<AXYZActor*> DeltaVisible, TSet<AXYZActor*> DeltaNonVisible, int32 _TeamId)
{
	TeamId = _TeamId;
	for(AXYZActor* VisibleActor : DeltaVisible)
	{
		VisibleActors.Add(VisibleActor);
	}

	for(AXYZActor* NonVisibleActor : DeltaNonVisible)
	{
		if(VisibleActors.Contains(NonVisibleActor))
		{
			VisibleActors.Remove(NonVisibleActor);
		}
	}
}

