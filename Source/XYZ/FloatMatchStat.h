#pragma once

#include "CoreMinimal.h"
#include "FloatMatchStat.generated.h"

USTRUCT(BlueprintType)
struct FFloatMatchStat
{
	GENERATED_BODY()
	
	float CumulativeTotal;

	TMap<float, float> ValuesByTime;
	int32 TeamId;

	void AddValue(float Time, float Value);
};

inline void FFloatMatchStat::AddValue(float Time, float Value)
{
	CumulativeTotal += Value;
	ValuesByTime.Add(Time, Value);
}
