// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZActionState.h"
#include "XYZAction.generated.h"

/**
 * 
 */
UCLASS()
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

public:
    // Target actor
    UPROPERTY(BlueprintReadWrite, Category = "Input")
        class AXYZActor* TargetActor;

    // Target location
    UPROPERTY(BlueprintReadWrite, Category = "Action")
        FVector TargetLocation;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        EXYZActionState ActionState = EXYZActionState::QUEUED;

    UPROPERTY()
        class AXYZActor* Actor;

    UPROPERTY()
        TSet<AXYZActor*> ActorSet;

    UFUNCTION()
        virtual void ProcessAction(float DeltaTime) {
        if (ActionState != EXYZActionState::IN_PROGRESS)
        {
            return;
        }
        if (!Actor)
        {
            CancelAction();
            return;
        }
    };

public:
    UPROPERTY(BlueprintReadWrite, Category = "Input")
        bool bQueueInput;

    UFUNCTION()
        void TryAction(float DeltaTime);
    UFUNCTION()
        virtual void StartAction();
    UFUNCTION()
        virtual void CompleteAction();
    UFUNCTION()
        virtual void CancelAction();

    UFUNCTION()
        bool IsFlaggedForDeuque() {
        return ActionState == EXYZActionState::COMPLETE || ActionState == EXYZActionState::CANCELLED;
        }
};
