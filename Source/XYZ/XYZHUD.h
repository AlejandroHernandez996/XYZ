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
	virtual void BeginPlay() override;
	void DrawHUD() override;
	UPROPERTY()
	TArray<class AXYZActor*> SelectedActors;
	UPROPERTY()
	TArray<class AXYZActor*> AllActorsOnScreen;
	FVector2D BoxStart;
	FVector2D BoxEnd;
	bool bSelectActors;
	FVector2D TopLeft;
	FVector2D BottomRight;
	UPROPERTY()
	class AXYZPlayerController* XYZPlayerController;

	UFUNCTION()
	void ClearActors() {
		SelectedActors.Empty();
		AllActorsOnScreen.Empty();
	}
};
