// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZAttackAction : public UXYZAction
{
	GENERATED_BODY()
public:
	virtual void ProcessAction(TSet<AXYZActor*> Agents) override;
	virtual bool HasAgentComplete(class AXYZActor* Agent) override;
};