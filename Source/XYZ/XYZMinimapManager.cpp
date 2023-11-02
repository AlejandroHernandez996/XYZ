// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZMinimapManager.h"
#include "XYZActor.h"
#include "XYZCameraController.h"
#include "XYZResourceActor.h"

// Sets default values
AXYZMinimapManager::AXYZMinimapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AXYZMinimapManager::BeginPlay()
{
	Super::BeginPlay();
	GridCellSize = 10000/MinimapSize;
}

void AXYZMinimapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FVector2D> UnitCoords;
	TArray<FColor> UnitColors;

	for (auto It = VisibleActors.CreateIterator(); It; ++It)
	{
		AXYZActor* Actor = *It;
		if (Actor && Actor->State == EXYZUnitState::DEAD)
		{
			It.RemoveCurrent();
		}
	}
	
	for(AXYZActor* VisibleActor : VisibleActors)
	{
		if(!VisibleActor) continue;
		if(VisibleActor->State == EXYZUnitState::DEAD) continue;
		if(VisibleActor->TeamId != TeamId && VisibleActor->bIsCloaked && !VisibleActor->bInEnemyTrueVision)
		{
			continue;
		}
		UnitCoords.Add(FVector2D(MinimapSize-FMath::FloorToInt(VisibleActor->GetActorLocation().X / GridCellSize),
							MinimapSize-FMath::FloorToInt(VisibleActor->GetActorLocation().Y / GridCellSize)));
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
	if(CameraController)
	{
		TArray<FVector2D> CameraCorners = CameraController->GetCameraCorners();
		TArray<FVector2D> CameraCornersToMinimapCoords;

		for(FVector2D CameraCorner : CameraCorners)
		{
			CameraCornersToMinimapCoords.Add(FVector2D(MinimapSize-FMath::FloorToInt(CameraCorner.X / GridCellSize),
							MinimapSize-FMath::FloorToInt(CameraCorner.Y / GridCellSize)));
		}
		if(CameraCorners.Num() == 4)
		{
			OnUpdateCamera.Broadcast(
				CameraCornersToMinimapCoords[0],
				CameraCornersToMinimapCoords[1],
				CameraCornersToMinimapCoords[2],
				CameraCornersToMinimapCoords[3],
				TeamId);
		}
	}
}

void AXYZMinimapManager::UpdateVisibleActors(TSet<AXYZActor*> DeltaVisible, TSet<AXYZActor*> DeltaNonVisible, int32 _TeamId)
{
	TeamId = _TeamId;
	for(AXYZActor* VisibleActor : DeltaVisible)
	{
		if(!VisibleActor) continue;
		VisibleActors.Add(VisibleActor);
	}

	for(AXYZActor* NonVisibleActor : DeltaNonVisible)
	{
		if(!NonVisibleActor) continue;
		if(VisibleActors.Contains(NonVisibleActor))
		{
			VisibleActors.Remove(NonVisibleActor);
		}
	}
}

