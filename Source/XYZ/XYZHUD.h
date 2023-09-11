// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "XYZHUD.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void DrawHUD() override;
	UPROPERTY()
	TArray<class AXYZActor*> SelectedActors;
	FVector2D BoxStart, BoxEnd;
	bool bSelectActors;

	void ClearActors() {
		SelectedActors.Empty();
	}
};
