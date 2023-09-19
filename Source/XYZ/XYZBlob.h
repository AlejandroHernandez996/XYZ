#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZActor.h"
#include "XYZBlob.generated.h"

UCLASS()
class XYZ_API UXYZBlob : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 BlobId;
    UPROPERTY()
    TSet<AXYZActor*> AgentsInBlob;

    TMap<AXYZActor*, TSharedPtr<FActionList>> AgentToNodeCache;

    UPROPERTY()
    int32 ActionListSize = 0;
    TSharedPtr<FActionList> Head;
    TSharedPtr<FActionList> Tail;

    UFUNCTION()
    virtual void ProcessBlob();
    UFUNCTION()
    void InitializeBlob();
    UFUNCTION()
    bool IsBlobProcessable();
    UFUNCTION()
    void AddAction(class UXYZAction* Action);
    UFUNCTION()
    void RemoveAgent(AXYZActor* Agent);

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
struct FActionList
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY()
        class UXYZAction* Action;
        TSharedPtr<FActionList> Next;
        TSharedPtr<FActionList> Previous;
    UPROPERTY()
        TSet<AXYZActor*> QueuedAgents;
    UPROPERTY()
        TSet<AXYZActor*> ProcessingAgents;
    UPROPERTY()
        TSet<AXYZActor*> CompletedAgents;

    void RemoveAgent(AXYZActor* Agent) {
        QueuedAgents.Remove(Agent);
        ProcessingAgents.Remove(Agent);
        CompletedAgents.Remove(Agent);
    }
};