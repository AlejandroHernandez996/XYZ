#pragma once

#include "CoreMinimal.h"
#include "DeathStruct.h"
#include "XYZDeathManager.generated.h"

UCLASS()
class XYZ_API UXYZDeathManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void QueueDeath(class AXYZActor* Actor);
	UFUNCTION()
	void ProcessDeaths(float DeltaTime);
    
	UPROPERTY()
	TArray<FDeathStruct> DeathQueue;

	float CurrentTime;
};