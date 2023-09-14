#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZActor.h"
#include "XYZBlob.generated.h"

UCLASS(Abstract)
class XYZ_API UXYZBlob : public UObject
{
    GENERATED_BODY()

public:
    int32 BlobId;

    bool bInProgress;
    bool bOverrideBlob;

    FVector TargetLocation;
    FVector InitialCenter;
    float AgentDensity;

    UPROPERTY()
        class AXYZActor* CenterAgent;
    UPROPERTY()
    TSet<AXYZActor*> AgentsInBlob;
    TQueue<UXYZAction*> ActionQueue;

    UPROPERTY()
        class AXYZActor* TargetActor;

    virtual void ProcessBlob();
    void FindCenterAgent();
    void FindInitialCenterLocation();

    FString ToString() const
    {
        FString result;

        result.Append(FString::Printf(TEXT("BlobId: %d, AgentCount: %d, Agents: ["), BlobId, AgentsInBlob.Num()));

        for (AXYZActor* Agent : AgentsInBlob)
        {
            if (Agent)
            {
                result.Append(FString::Printf(TEXT("%d, "), Agent->UActorId));
            }
        }
        result.Append(TEXT("]"));

        return result;
    }
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