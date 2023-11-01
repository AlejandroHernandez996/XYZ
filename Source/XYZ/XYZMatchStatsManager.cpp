// Copyright © 2023 XYZRTS. All Rights Reserved.


#include "XYZMatchStatsManager.h"

#include "XYZGameState.h"


void UXYZMatchStatsManager::Initialize()
{
	IntStatsByTeam.SetNum(2);

	for (int32 TeamIndex = 0; TeamIndex < IntStatsByTeam.Num(); TeamIndex++)
	{
		for (int32 EnumValue = static_cast<int32>(EMatchStatType::MINERALS_GATHERED);
			 EnumValue <= static_cast<int32>(EMatchStatType::SUPPLY);
			 EnumValue++)
		{
			TSharedPtr<FIntMatchStat> MatchStat = MakeShared<FIntMatchStat>();
			MatchStat->TeamId = TeamIndex;
			EMatchStatType StatType = static_cast<EMatchStatType>(EnumValue);
			MatchStat->AddValue(0.0f, 0);
			IntStatsByTeam[TeamIndex].Add(StatType, MatchStat);
		}
	}
}

void UXYZMatchStatsManager::Process(float DeltaTime)
{
	for(TSharedPtr<FMatchStatPayload> StatPayload : StatsToProcess)
	{
		if(StatPayload->bIsIntValue)
		{
			if(IntStatsByTeam.IsValidIndex(StatPayload->TeamId) && IntStatsByTeam[StatPayload->TeamId].Contains(StatPayload->StatType))
			{
				IntStatsByTeam[StatPayload->TeamId][StatPayload->StatType]->AddValue(MatchTime, StatPayload->IntValue);
				UE_LOG(LogTemp, Warning, TEXT("Added Stat for Team %d, StatType %s, Value %d at MatchTime %.2f"),
					StatPayload->TeamId,
					*GetMatchStatString(StatPayload->StatType),
					StatPayload->IntValue,
					MatchTime
				);
			}
		}else
		{
			if(FloatStatsByTeam.IsValidIndex(StatPayload->TeamId) && FloatStatsByTeam[StatPayload->TeamId].Contains(StatPayload->StatType))
			{
				FloatStatsByTeam[StatPayload->TeamId][StatPayload->StatType]->AddValue(MatchTime, StatPayload->FloatValue);
			}
		}
	}
	StatsToProcess.Empty();
	MatchTime += DeltaTime;
}

void UXYZMatchStatsManager::AddIntStat(TSharedPtr<FMatchStatPayload> MatchStatPayload)
{
	if(!MatchStatPayload) return;
	MatchStatPayload->bIsIntValue = true;
	StatsToProcess.Add(MatchStatPayload);
}

void UXYZMatchStatsManager::AddFloatStat(TSharedPtr<FMatchStatPayload> MatchStatPayload)
{
	if(!MatchStatPayload) return;
	MatchStatPayload->bIsIntValue = false;
	StatsToProcess.Add(MatchStatPayload);
}

void UXYZMatchStatsManager::PrintMatchStats()
{
	for (int32 TeamIndex = 0; TeamIndex < IntStatsByTeam.Num(); TeamIndex++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Team %d Stats:"), TeamIndex);

		TMap<EMatchStatType, TSharedPtr<FIntMatchStat>> TeamStats = IntStatsByTeam[TeamIndex];

		for (const auto& StatPair : TeamStats)
		{
			EMatchStatType StatType = StatPair.Key;
			TSharedPtr<FIntMatchStat> Stat = StatPair.Value;

			FString StatName = GetMatchStatString(StatType);
			UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *StatName, Stat->CumulativeTotal);

			UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *StatName, Stat->CumulativeTotal/MatchTime);

			UE_LOG(LogTemp, Warning, TEXT("Values over time:"));
			for (const auto& TimeValue : Stat->ValuesByTime)
			{
				float Time = TimeValue.Key;
				int32 Value = TimeValue.Value;
				UE_LOG(LogTemp, Warning, TEXT("Time: %.2f, Value: %d"), Time, Value);
			}
		}
	}
}