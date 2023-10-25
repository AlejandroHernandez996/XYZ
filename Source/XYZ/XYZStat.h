// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EXYZStat : uint8
{
	ARMOR,
	HEALTH,
	MAX_HEALTH,
	ENERGY,
	MAX_ENERGY,
	ATTACK,
	ATTACK_RANGE,
	VISION_RANGE,
	ATTACK_RATE,
	MOVEMENT_SPEED,
	CLOAK
};