// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZEvadeAction.generated.h"

/**
 *
 */
UCLASS()
class XYZ_API UXYZEvadeAction : public UXYZAction
{
	GENERATED_BODY()
public:
	virtual void ProcessAction(float DeltaTime) override;

	void CancelAction() override;
	void CompleteAction() override;
};
