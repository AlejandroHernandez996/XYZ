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
		virtual void ProcessAction(float DeltaTime) override;
public:
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		float TargetLocationThreshold = 1.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
		bool bIgnoreAllies = true;
	void CancelAction() override;
	void CompleteAction() override;
	bool bIsAttackMove;
};