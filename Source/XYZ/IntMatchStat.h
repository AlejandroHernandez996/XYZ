#pragma once

#include "CoreMinimal.h"
#include "IntMatchStat.generated.h"

USTRUCT(BlueprintType)
struct FIntMatchStat
{
	GENERATED_BODY()
	
	int32 CumulativeTotal;

	TMap<float, int32> ValuesByTime;
	int32 TeamId;

	void AddValue(float Time, int32 Value);
};

inline void FIntMatchStat::AddValue(float Time, int32 Value)
{
	CumulativeTotal += Value;
	ValuesByTime.Add(Time, Value);
}