// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZAction.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class XYZ_API UXYZAction : public UObject
{
	GENERATED_BODY()

public:
    UFUNCTION()
        void Initialize(AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput) {
        TargetActor = _TargetActor;
        bQueueInput = _bQueueInput;
        TargetLocation = _TargetLocation;
    }

    UFUNCTION()
    virtual bool IsContinousProcessing()
    {
        return false;
    }

public:
    UPROPERTY(BlueprintReadWrite, Category = "Input")
        class AXYZActor* TargetActor;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        FVector TargetLocation;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        bool bQueueInput;

    UFUNCTION()
        virtual void ProcessAction(TSet<AXYZActor*> Agents) {}
    UFUNCTION()
        virtual bool HasAgentComplete(AXYZActor* Agent) { return true; }
    UPROPERTY()
        TSet<AXYZActor*> ActorSet;
    UPROPERTY()
    int32 ProcessCount = 0;
    UPROPERTY()
    float ProcessRate = .5f;
    UPROPERTY()
    float TimeSinceProcess;
    UPROPERTY()
    float TimeSinceStart;
    UPROPERTY()
    float CompleteTimeThreshold = .2f;
};