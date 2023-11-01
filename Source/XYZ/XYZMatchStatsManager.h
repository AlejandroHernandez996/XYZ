// Copyright © 2023 XYZRTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FloatMatchStat.h"
#include "IntMatchStat.h"
#include "Processable.h"
#include "MatchStatType.h"
#include "UObject/NoExportTypes.h"
#include "XYZMatchStatsManager.generated.h"

struct FMatchStatPayload;
/**
 * 
 */
UCLASS()
class XYZ_API UXYZMatchStatsManager : public UObject, public IProcessable
{
	GENERATED_BODY()
public:
	virtual void Process(float DeltaTime) override;

	void Initialize();
	
	void AddIntStat(TSharedPtr<FMatchStatPayload> MatchStatPayload);
	void AddFloatStat(TSharedPtr<FMatchStatPayload> MatchStatPayload);
	void PrintMatchStats();

	TArray<TMap<EMatchStatType, TSharedPtr<FFloatMatchStat>>> FloatStatsByTeam;
	TArray<TMap<EMatchStatType, TSharedPtr<FIntMatchStat>>> IntStatsByTeam;

	TSet<TSharedPtr<FMatchStatPayload>> StatsToProcess;
	float MatchTime;

	UPROPERTY()
	class AXYZGameState* XYZGameState;
};

USTRUCT()
struct FMatchStatPayload
{
	GENERATED_BODY()

	EMatchStatType StatType;
	int32 TeamId;
	float FloatValue;
	int32 IntValue;
	bool bIsIntValue;
};
