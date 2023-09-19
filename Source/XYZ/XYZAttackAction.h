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
	virtual void ProcessAction(TSet<AXYZActor*> Agents) { return; }
	virtual bool HasAgentComplete(class AXYZActor* Agent) { return true; }
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		float TargetLocationThreshold = 1.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		bool bIgnoreAllies = true;
	bool bIsAttackMove;
};