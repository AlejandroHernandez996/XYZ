#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "GridCell.generated.h"

USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Grid")
	TSet<AXYZActor*> ActorsInCell;
	TArray<TSet<AXYZActor*>> ActorsWithVisionByTeam = {{}, {}};
	UPROPERTY()
	int32 Height = 0;
};