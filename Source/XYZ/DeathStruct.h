#pragma once

#include "CoreMinimal.h"
#include "DeathStruct.generated.h"

USTRUCT(BlueprintType)
struct FDeathStruct
{
	GENERATED_BODY()
	FDeathStruct()
		: Actor(nullptr), TimeToDie(0.0f), TimeToRemoveVision(0.0f), bRemovedVision(false)
	{
	}
	FDeathStruct(class AXYZActor* _Actor, float _TimeToDie, float _TimeToRemoveVision)
	{
		Actor = _Actor;
		TimeToDie = _TimeToDie;
		TimeToRemoveVision = _TimeToRemoveVision;
		bRemovedVision = false;
	}
	UPROPERTY()
	class AXYZActor* Actor;
    
	UPROPERTY()
	float TimeToDie;

	UPROPERTY()
	float TimeToRemoveVision;
	UPROPERTY()
	bool bRemovedVision;
};