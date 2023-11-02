#pragma once

#include "CoreMinimal.h"
#include "MatchStatType.h"
#include "IntMatchStat.generated.h"

USTRUCT(BlueprintType)
struct FIntMatchStat
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 CumulativeTotal;
	UPROPERTY(BlueprintReadWrite)
	TMap<float, int32> ValuesByTime;
	UPROPERTY(BlueprintReadWrite)
	int32 TeamId;
	UPROPERTY(BlueprintReadWrite)
	FString StatName;
	UPROPERTY(BlueprintReadWrite)
	EMatchStatType StatType;

	void AddValue(float Time, int32 Value);
};

inline void FIntMatchStat::AddValue(float Time, int32 Value)
{
	CumulativeTotal += Value;
	ValuesByTime.Add(Time, Value);
}