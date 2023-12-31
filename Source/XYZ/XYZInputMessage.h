// InputMessage.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZInputType.h"
#include "XYZActor.h"
#include "Engine/EngineTypes.h" // For GEngine
#include "Misc/OutputDeviceRedirector.h" // For GLog
#include "XYZInputMessage.generated.h"

// Forward declaration
class AXYZActor;

USTRUCT(BlueprintType)
struct FXYZInputMessage
{
    GENERATED_BODY();

    UPROPERTY()
        TArray<int32> SelectedActors;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        int32 XYZTargetActor;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        FVector TargetLocation;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        EXYZInputType InputType;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        bool bQueueInput;

    UPROPERTY()
        int32 Tick;

    UPROPERTY()
        int32 AbilityIndex = -1;
    UPROPERTY()
        int32 ActiveActorId = -1;

    FXYZInputMessage()
    {
        XYZTargetActor = -1;
        Tick = -1;
        TargetLocation = FVector::ZeroVector;
        InputType = EXYZInputType::NONE;
        bQueueInput = false;
    }

    FXYZInputMessage(TArray<int32> _SelectedActors, int32 _XYZTargetActor, FVector _TargetLocation, EXYZInputType _InputType, bool _bQueueInput)
    {
        SelectedActors = _SelectedActors;
        XYZTargetActor = _XYZTargetActor;
        TargetLocation = _TargetLocation;
        InputType = _InputType;
        bQueueInput = _bQueueInput;
    }

    FXYZInputMessage(FXYZInputMessage InputMessage, int32 _Tick)
    {
        SelectedActors = InputMessage.SelectedActors;
        XYZTargetActor = InputMessage.XYZTargetActor;
        TargetLocation = InputMessage.TargetLocation;
        InputType = InputMessage.InputType;
        bQueueInput = InputMessage.bQueueInput;
        Tick = _Tick;
    }

    FString ToString() const
    {
        FString result;

        result += "XYZ Target Actor: " + FString::Printf(TEXT("%d"), XYZTargetActor) + "\n";
        result += "Target Location: " + TargetLocation.ToString() + "\n";
        result += "Input Type: " + FString::Printf(TEXT("%d"), static_cast<uint8>(InputType)) + "\n";
        result += "Queue Input: " + FString(bQueueInput ? "true" : "false") + "\n";

        // Optionally convert SelectedUnits array to string
        result += "Selected Units: ";
        for (int32 ActorId : SelectedActors)
        {
            result += FString::Printf(TEXT("%d"), ActorId);
            result += ", ";
        }
        result += "\n";
        result += "Tick: " + FString::Printf(TEXT("%d"), Tick) + "\n";

        return result;
    }
};