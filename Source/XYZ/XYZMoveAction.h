// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZMoveAction.generated.h"

UCLASS()
class XYZ_API UXYZMoveAction : public UXYZAction
{
	GENERATED_BODY()

public:
	virtual void ProcessAction(TSet<AXYZActor*> Agents) override;
	virtual bool HasAgentComplete(class AXYZActor* Agent) override;
	void MovePack(TSharedPtr<FAgentPack> AgentPack, int32 LayerIndex, bool bIsAttackMove);
	void FillPack(TSharedPtr<FAgentPack> AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex);
	UFUNCTION()
	class AXYZActor* FindCenterAgent(TSet<AXYZActor*> Agents, FVector CenterLocation);
	UFUNCTION()
	FVector FindInitialCenterLocation(TSet<AXYZActor*> Agents);
    UFUNCTION()
    void CreateAgentGroups(TSet<AXYZActor*> Agents);
    void FindAndAddNeighbors(class UXYZMapManager* MapManager, AXYZActor* Agent, TSharedPtr<FAgentGroup> AgentGroup, TSet<FIntVector2>& SearchedCoords, TSet<AXYZActor*>& ActorsToAdd, TSet<AXYZActor*>& AgentsInAction);
    bool IsGroupComplete(TSharedPtr<FAgentGroup> AgentGroup);
    void CalculateDensityForGroup(TSharedPtr<FAgentGroup> AgentGroup);
    void MoveGroup(TSharedPtr<FAgentGroup> AgentGroup);

    virtual bool IsContinousProcessing() override
    {
        return true;
    }
    
    UPROPERTY()
    TSet<AXYZActor*> CompletedAgents;
    
    TMap<AXYZActor*, TSharedPtr<FAgentGroup>> AgentsWithGroup;
    TSet<TSharedPtr<FAgentGroup>> AgentGroups;
};

USTRUCT()
struct FAgentGroup
{
    GENERATED_BODY()
    
    UPROPERTY()
    TSet<AXYZActor*> AgentsInGroup;
    UPROPERTY()
    AXYZActor* CenterAgent;
    UPROPERTY()
    FIntVector2 CenterCoord;
    UPROPERTY()
    float Density;
    UPROPERTY()
    bool bIsMoving;
};

USTRUCT()
struct FAgentPack
{
    GENERATED_USTRUCT_BODY()
public:
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
