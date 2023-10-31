#pragma once

#include "CoreMinimal.h"
#include "DeathStruct.h"
#include "Processable.h"
#include "XYZDeathManager.generated.h"

UCLASS()
class XYZ_API UXYZDeathManager : public UObject, public IProcessable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void QueueDeath(class AXYZActor* Actor);
	UFUNCTION()
	void Process(float DeltaSeconds);
    
	TSet<TSharedPtr<FDeathStruct>> DeathQueue;

	float CurrentTime;
};