#pragma once

#include "CoreMinimal.h"
#include "GridCell.generated.h"

class AXYZActor;

USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Grid")
	TSet<AXYZActor*> ActorsInCell;
	UPROPERTY()
	TArray<bool> TeamVision = {false, false};
	UPROPERTY()
	int32 Height = 0;
};