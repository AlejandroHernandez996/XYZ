// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZMoveAction.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZMoveAction : public UXYZAction
{
	GENERATED_BODY()

public:
	virtual void ProcessAction(TSet<AXYZActor*> Agents) override;
	virtual bool HasAgentComplete(class AXYZActor* Agent) override;
	void MovePack(TSharedPtr<FAgentPack> AgentPack, int32 LayerIndex);
	void FillPack(TSharedPtr<FAgentPack> AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex);
	UFUNCTION()
	class AXYZActor* FindCenterAgent(TSet<AXYZActor*> Agents, FVector CenterLocation);
	UFUNCTION()
	FVector FindInitialCenterLocation(TSet<AXYZActor*> Agents);
};

USTRUCT()
struct FAgentPack
{
    GENERATED_USTRUCT_BODY()
public:
        float DISTANCE_FROM_AGENT = 120.0f;
    UPROPERTY()
        TArray<AXYZActor*> Agents;
    UPROPERTY()
        TArray<FVector> SectorDirections;
    UPROPERTY()
        AXYZActor* CenterAgent;
    TSharedPtr<FAgentPack> NextPack;

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
