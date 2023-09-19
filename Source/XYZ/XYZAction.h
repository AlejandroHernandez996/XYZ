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
    UPROPERTY(BlueprintReadWrite, Category = "Input")
        FVector TargetLocation;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        EXYZActionState ActionState = EXYZActionState::QUEUED;

    UPROPERTY(BlueprintReadWrite, Category = "Input")
        bool bQueueInput;

    UFUNCTION()
        virtual void ProcessAction(TSet<AXYZActor*> Agents) {}

    UFUNCTION()
        virtual bool HasAgentComplete(AXYZActor* Agent) { return true; }
    UFUNCTION()
        class AXYZActor* FindCenterAgent(TSet<AXYZActor*> Agents, FVector CenterLocation);
    UFUNCTION()
        FVector FindInitialCenterLocation(TSet<AXYZActor*> Agents);

    UPROPERTY()
        TSet<AXYZActor*> ActorSet;
};

USTRUCT()
struct FAgentPack
{
    GENERATED_USTRUCT_BODY()

    float DISTANCE_FROM_AGENT = 120.0f;
    TArray<AXYZActor*> Agents;
    TArray<FVector> SectorDirections;
    TSharedPtr<FAgentPack> NextPack;
    AXYZActor* CenterAgent;

    int32 GetLayerNodeCount(int32 Layer) {
        return 1 + 3 * Layer * (Layer + 1);
    }

    void SetSectorDirections(int32 NumberOfSectors) {
        for (int32 i = 0; i < NumberOfSectors; ++i)
        {
            float Angle = i * 2 * PI / NumberOfSectors; // Divide circle into 6 sectors
            FVector Direction(FMath::Cos(Angle), FMath::Sin(Angle), 0);
            SectorDirections.Add(Direction);
        }
    }
};
