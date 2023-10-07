#pragma once

#include "CoreMinimal.h"
#include "ActorCount.generated.h"


USTRUCT()
struct FActorCount
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
	TMap<int32, int32> ActorCounts;
};
