// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EXYZActionState : uint8
{
	QUEUED,
	IN_PROGRESS,
	COMPLETE,
	CANCELLED
};