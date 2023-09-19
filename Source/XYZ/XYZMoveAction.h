// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZMoveAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZMoveAction : public UXYZAction
{
	GENERATED_BODY()

public:
	virtual void ProcessAction(TSet<AXYZActor*> Agents);
	virtual bool HasAgentComplete(class AXYZActor* Agent);
	virtual void MovePack(FAgentPack* AgentPack, int32 LayerIndex);
	void FillPack(FAgentPack* AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex);
	UPROPERTY(BlueprintReadWrite, Category = "Move")
		float TargetLocationThreshold = 1.0f;

};
