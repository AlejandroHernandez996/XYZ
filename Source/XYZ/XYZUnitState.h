// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EXYZUnitState : uint8
{
	IDLE,
	ATTACK,
	MOVE,
};