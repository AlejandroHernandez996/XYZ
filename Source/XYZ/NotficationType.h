#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ENotificationType : uint8
{
	NOTIFY_RESEARCH_COMPLETE = 0,
	NOTIFY_BUILDING_COMPLETE = 1,
	NOTIFY_UNIT_TRAINED = 2,
	NOTIFY_MINERALS_REQUIRED = 3,
	NOTIFY_GAS_REQUIRED = 4,
	NOTIFY_SUPPLY_REQUIRED = 5,
	NOTIFY_UNITS_UNDER_ATTACK = 6,
	NOTIFY_BUILDINGS_UNDER_ATTACK = 7,
	NOTIFY_UPGRADE_REQUIRED = 8,
};


static TMap<ENotificationType, FString> NotificationTypeStrings
{
			{ENotificationType::NOTIFY_RESEARCH_COMPLETE, TEXT("Research Complete")},
			{ENotificationType::NOTIFY_BUILDING_COMPLETE, TEXT("Building Complete")},
			{ENotificationType::NOTIFY_UNIT_TRAINED, TEXT("Unit Trained")},
			{ENotificationType::NOTIFY_MINERALS_REQUIRED, TEXT("Minerals Required")},
			{ENotificationType::NOTIFY_GAS_REQUIRED, TEXT("Gas Required")},
			{ENotificationType::NOTIFY_SUPPLY_REQUIRED, TEXT("Supply Required")},
			{ENotificationType::NOTIFY_UNITS_UNDER_ATTACK, TEXT("Units Under Attack")},
			{ENotificationType::NOTIFY_BUILDINGS_UNDER_ATTACK, TEXT("Buildings Under Attack")},
			{ENotificationType::NOTIFY_UPGRADE_REQUIRED, TEXT("Upgrade Required")}
};

inline FString GetNotificationTypeString(ENotificationType Type)
{
	if (NotificationTypeStrings.Contains(Type))
	{
		return NotificationTypeStrings[Type];
	}
	return FString(TEXT("Unknown"));
}