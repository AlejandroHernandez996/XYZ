#pragma once

#include "CoreMinimal.h"
#include "XYZBlob.h"
#include "XYZSimpleMovingBlob.generated.h"

UCLASS()
class XYZ_API UXYZSimpleMovingBlob : public UXYZBlob
{
    GENERATED_BODY()

public:
    FVector TargetLocation;
    FVector InitialCenter;
    void FindInitialCenterLocation();
    void MovePack(FAgentPack* AgentPack, int32 LayerIndex);
    void FillPack(FAgentPack* AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex);
    virtual void ProcessBlob() override;

    int32 SortedAgentIndex = 0;
    FVector CurrentTargetLocation;
    float AgentDensity;

};

USTRUCT()
struct FAgentPack
{
    GENERATED_USTRUCT_BODY()

    float DISTANCE_FROM_AGENT = 175.0f;
    
    TArray<AXYZActor*> Agents;
    
    TArray<FVector> SectorDirections;

    TSharedPtr<FAgentPack> NextPack;

    int32 GetLayerNodeCount(int32 Layer) {
        return 1 + 3 * Layer * (Layer + 1);
    }

    void SetSectorDirections(int32 NumberOfSectors) {
        for (int32 i = 0; i < NumberOfSectors; ++i)
        {
            float Angle = i * 2*PI / NumberOfSectors; // Divide circle into 6 sectors
            FVector Direction(FMath::Cos(Angle), FMath::Sin(Angle), 0);
            SectorDirections.Add(Direction);
        }
    }
};