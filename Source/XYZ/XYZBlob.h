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

        // Remove trailing ", "
        if (result.EndsWith(TEXT(", ")))
        {
            result.RemoveAt(result.Len() - 2, 2, false);
        }

        result.Append(TEXT("]"));

        return result;
    }
};