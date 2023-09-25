// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMainMenuStateEnum : uint8
{
	PRE_LOGGING_IN,
	LOGGING_IN,
	LOGGED_IN,
	FINDING_SESSION,
	FOUND_SESSION,
	JOINING_SESSION,
	JOINED_SESSION,
	CONNECTING_SESSION,
	CONNECTED_SESSION
};