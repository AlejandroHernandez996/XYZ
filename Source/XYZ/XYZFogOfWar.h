#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZFogOfWar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRevealCell, FVector2D, Coord);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConcealCell, FVector2D, Coord);

UCLASS()
class XYZ_API AXYZFogOfWar : public AActor
{
	GENERATED_BODY()

public:	
	AXYZFogOfWar();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FRevealCell OnRevealCell;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FConcealCell OnConcealCell;
	
	UFUNCTION()
	void RevealCell(FVector2D Coord);
	UFUNCTION()
	void ConcealCell(FVector2D Coord);
	UFUNCTION()
	void SetPlayerController(AXYZPlayerController* PlayerController);
	UFUNCTION()
	void Update(const TArray<FVector2D> Visible, const TArray<FVector2D> NonVisible);
	UPROPERTY()
	TSet<FVector2D> RevealCoords;
	UPROPERTY()
	float TimeSinceBegin;
	UPROPERTY()
	class AXYZPlayerController* OwningController;
	TQueue<TArray<TArray<FVector2d>>> CellsToUpdate;

};