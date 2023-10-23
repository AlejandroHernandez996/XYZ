#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EXYZAbilityState : uint8
{
	IDLE,
	SELECTED,
	ACTIVATED
};