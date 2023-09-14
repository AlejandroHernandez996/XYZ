#pragma once

#include "CoreMinimal.h"
#include "XYZBlob.h"
#include "XYZSimpleAttackMovingBlob.generated.h"

UCLASS()
class XYZ_API UXYZSimpleAttackMovingBlob : public UXYZBlob
{
    GENERATED_BODY()

public:
    virtual void MovePack(FAgentPack* AgentPack, int32 LayerIndex);
    void FillPack(FAgentPack* AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex);
    virtual void ProcessBlob() override;

    int32 SortedAgentIndex = 0;
    FVector CurrentTargetLocation;
};