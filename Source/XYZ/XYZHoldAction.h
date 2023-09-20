// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZHoldAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZHoldAction : public UXYZAction
{
	GENERATED_BODY()
public:
    virtual void ProcessAction(TSet<AXYZActor*> Agents) override;
    virtual bool HasAgentComplete(AXYZActor* Agent) { return true; }
};
