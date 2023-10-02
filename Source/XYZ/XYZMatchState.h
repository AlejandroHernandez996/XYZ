// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EXYZMatchState : uint8
{
	WAITING_FOR_PLAYERS,
	MATCH_STARTING,
	IN_PROGRESS,
	CLEANING_UP,
	SHUTTING_DOWN,
	GAME_OVER
};