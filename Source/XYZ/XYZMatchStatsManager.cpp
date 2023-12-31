#include "XYZMatchStatsManager.h"

#include "XYZActor.h"
#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "XYZWorker.h"


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
			MatchStat->StatType = static_cast<EMatchStatType>(EnumValue);
			MatchStat->StatName = GetMatchStatString(MatchStat->StatType);
			EMatchStatType StatType = static_cast<EMatchStatType>(EnumValue);
			MatchStat->AddValue(0.0f, 0);
			IntStatsByTeam[TeamIndex].Add(StatType, MatchStat);
		}
	}
}

void UXYZMatchStatsManager::Process(float DeltaTime)
{
	if(MatchTime == 0.0f)
	{
		for(int i = 0;i < 2;i++)
		{
			int32 InitialSupply = XYZGameState->SupplyByTeamId[i*2];
			AddIntStat(InitialSupply,EMatchStatType::SUPPLY,i);
			TArray<AXYZActor*> Actors;
			XYZGameState->ActorsByUID.GenerateValueArray(Actors);

			int32 InitialWorkerCount = 0;
			for(AXYZActor* Actor : Actors)
			{
				if(Actor->TeamId == i && Actor->IsA(AXYZWorker::StaticClass()))
				{
					InitialWorkerCount++;
				}
			}
			AddIntStat(InitialWorkerCount,EMatchStatType::WORKER_COUNT,i);
		}
	}
	
	for(TSharedPtr<FMatchStatPayload> StatPayload : StatsToProcess)
	{
		if(StatPayload->bIsIntValue)
		{
			if(IntStatsByTeam.IsValidIndex(StatPayload->TeamId) && IntStatsByTeam[StatPayload->TeamId].Contains(StatPayload->StatType))
			{
				IntStatsByTeam[StatPayload->TeamId][StatPayload->StatType]->AddValue(MatchTime, StatPayload->IntValue);
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

void UXYZMatchStatsManager::AddIntStat(int32 Value, EMatchStatType StatType, int32 TeamId)
{
	TSharedPtr<FMatchStatPayload> MatchStatPayload = MakeShared<FMatchStatPayload>(FMatchStatPayload());
	MatchStatPayload->TeamId = TeamId;
	MatchStatPayload->IntValue = Value;
	MatchStatPayload->StatType = StatType;
	AddIntStat(MatchStatPayload);
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

void UXYZMatchStatsManager::SendMatchStats(TSet<AXYZPlayerController*> PlayerControllers)
{
	TArray<FIntMatchStat> Team1Stats;
	TArray<FIntMatchStat> Team2Stats;

	for(int i =0;i < PlayerControllers.Num();i++)
	{
		TArray<TSharedPtr<FIntMatchStat>> TeamStats;
		IntStatsByTeam[i].GenerateValueArray(TeamStats);
		for(TSharedPtr<FIntMatchStat> MatchStat : TeamStats)
		{
			if(i == 0)
			{
				Team1Stats.Add(MatchStat.ToSharedRef().Get());	
			}else
			{
				Team2Stats.Add(MatchStat.ToSharedRef().Get());	
			}
		}
	}

	for(AXYZPlayerController* PlayerController : PlayerControllers)
	{
		PlayerController->SendMatchStats(Team1Stats,Team2Stats);
	}

}