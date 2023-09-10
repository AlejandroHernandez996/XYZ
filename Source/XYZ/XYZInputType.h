// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EXYZInputType : uint8
{
	PRIMARY_INPUT,
	SECONDARY_INPUT,
	ATTACK_MOVE,
	PRIMARY_MOD,
	SECONDARY_MOD,
	NONE,
	CLEAR,
	STOP,
};