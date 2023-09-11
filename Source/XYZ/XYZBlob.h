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
    TSet<AXYZActor*> AgentsInBlob;
    class UXYZAction* Action;
    int32 BlobId;
    bool bInProgress;
    virtual void ProcessBlob();
};