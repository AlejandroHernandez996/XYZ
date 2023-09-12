// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZSimpleMovingBlob.h"
#include "XYZSimpleAttackMovingBlob.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZSimpleAttackMovingBlob : public UXYZSimpleMovingBlob
{
	GENERATED_BODY()

public:
	virtual void MovePack(FAgentPack* AgentPack, int32 Level) override;
};
