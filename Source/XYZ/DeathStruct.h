#pragma once

#include "CoreMinimal.h"
#include "DeathStruct.generated.h"

USTRUCT(BlueprintType)
struct FDeathStruct
{
	GENERATED_BODY()
	FDeathStruct()
		: Actor(nullptr), TimeToDie(0.0f)
	{
	}
	FDeathStruct(class AXYZActor* _Actor, float _TimeToDie)
	{
		Actor = _Actor;
		TimeToDie = _TimeToDie;
	}
	UPROPERTY()
	class AXYZActor* Actor;
    
	UPROPERTY()
	float TimeToDie;
};