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
        void Initialize(AXYZActor* _Actor, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput) {
        Actor = _Actor;
        TargetActor = _TargetActor;
        bQueueInput = _bQueueInput;
        TargetLocation = _TargetLocation;
    }

protected:
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

    UFUNCTION()
        virtual void ProcessAction(float DeltaTime) {};

public:
    UPROPERTY(BlueprintReadWrite, Category = "Input")
        bool bQueueInput;

    UFUNCTION()
        void TryAction(float DeltaTime);

    UFUNCTION()
        virtual void StartAction() { 
            ActionState = EXYZActionState::IN_PROGRESS;
        }

    UFUNCTION()
        virtual void CompleteAction() {
            ActionState = EXYZActionState::COMPLETE;
        }

    UFUNCTION()
        virtual void CancelAction() {
            ActionState = EXYZActionState::CANCELLED;
        }

    UFUNCTION()
        bool IsFlaggedForDeuque() {
        return ActionState == EXYZActionState::COMPLETE || ActionState == EXYZActionState::CANCELLED;
        }
};
