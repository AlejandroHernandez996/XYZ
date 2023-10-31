// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZMapManager.h"
#include "GameFramework/Actor.h"
#include "XYZMinimapManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateMinimap, const TArray<FVector2D>&, UnitBlots, const TArray<FColor>&, UnitColor,const int32& ,TeamId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FUpdateCameraMarker, const FVector2D&, TopLeft, const FVector2D&, TopRight, const FVector2D&, BottomLeft, const FVector2D&, BottomRight, const int32&, TeamId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClearMinimap, const int32&, TeamId);

UCLASS()
class XYZ_API AXYZMinimapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXYZMinimapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AXYZPlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AXYZGameState* GameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinimapSize = 128;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UnitSize = 1.5f;
	int32 GridCellSize;
	UPROPERTY(BlueprintAssignable)
	FUpdateMinimap OnUpdateMinimap;
	UPROPERTY(BlueprintAssignable)
	FClearMinimap OnClearMinimap;
	UPROPERTY(BlueprintAssignable)
	FUpdateCameraMarker OnUpdateCamera;
	UPROPERTY()
	TSet<class AXYZActor*> VisibleActors;
	UPROPERTY()
	class AXYZCameraController* CameraController;
	int32 TeamId = -1;
	UFUNCTION()
	void UpdateVisibleActors(TSet<AXYZActor*> DeltaVisible, TSet<AXYZActor*> DeltaNonVisible, int32 TeamId);
};
