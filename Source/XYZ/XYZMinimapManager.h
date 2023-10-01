// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZMinimapManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateMinimap, const TArray<FVector2D>&, UnitBlots, const TArray<FColor>&, UnitColor,const int32& ,TeamId);
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
	int32 MinimapSize = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UnitSize = 1.0f;

	UPROPERTY(BlueprintAssignable)
	FUpdateMinimap OnUpdateMinimap;
	UPROPERTY(BlueprintAssignable)
	FClearMinimap OnClearMinimap;

	UPROPERTY()
	TSet<class AXYZActor*> VisibleActors;
	
	int32 TeamId = -1;
	UFUNCTION()
	void UpdateVisibleActors(TSet<AXYZActor*> DeltaVisible, TSet<AXYZActor*> DeltaNonVisible, int32 TeamId);
};
