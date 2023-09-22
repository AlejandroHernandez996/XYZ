// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZAbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZAbilityAction : public UXYZAction
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		int32 AbilityIndex;
	UPROPERTY()
		int32 ActiveActorId;
	virtual void ProcessAction(TSet<AXYZActor*> Agents) override;
	virtual bool HasAgentComplete(class AXYZActor* Agent) override;
};
