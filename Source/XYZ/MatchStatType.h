// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMatchStatType : uint8
{
	MINERALS_GATHERED = 0,
	GAS_GATHERED = 1,
	UNITS_KILLED = 2,
	BUILDINGS_DESTROYED = 3,
	UNITS_TRAINED = 4,
	BUILDINGS_PLACED = 5,
	APM = 6,
	WORKER_COUNT = 7,
	SUPPLY = 8
};

static TMap<EMatchStatType, FString> MatchStatStrings
{
	{EMatchStatType::MINERALS_GATHERED, TEXT("Minerals Gathered")},
	{EMatchStatType::GAS_GATHERED, TEXT("Gas Gathered")},
	{EMatchStatType::UNITS_KILLED, TEXT("Units Killed")},
	{EMatchStatType::BUILDINGS_DESTROYED, TEXT("Buildings Destroyed")},
	{EMatchStatType::UNITS_TRAINED, TEXT("Units Trained")},
	{EMatchStatType::BUILDINGS_PLACED, TEXT("Buildings Placed")},
	{EMatchStatType::SUPPLY, TEXT("Supply")},
	{EMatchStatType::WORKER_COUNT, TEXT("Worker Count")},
	{EMatchStatType::APM, TEXT("Actions Per Minute")},
};

inline FString GetMatchStatString(EMatchStatType MatchStat)
{
	if (MatchStatStrings.Contains(MatchStat))
	{
		return MatchStatStrings[MatchStat];
	}
	return FString(TEXT("Unknown"));
}