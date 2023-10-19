#pragma once

#include "CoreMinimal.h"
#include "XYZMapManager.h"
#include "GameFramework/Actor.h"
#include "XYZFogOfWar.generated.h"

class UXYZMapManager;
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
	void SetPlayerController(AXYZPlayerController* PlayerController);
	UFUNCTION()
	void Update(const TArray<FIntVector2> Visible, const TArray<FIntVector2> NonVisible);
	UPROPERTY()
	TSet<FIntVector2> RevealCoords;
	UPROPERTY()
	float TimeSinceBegin;
	UPROPERTY()
	class AXYZPlayerController* OwningController;
	TQueue<TArray<TArray<FIntVector2>>> CellsToUpdate;
	UPROPERTY(BlueprintReadWrite)
	int32 GRID_SIZE = 128;

};