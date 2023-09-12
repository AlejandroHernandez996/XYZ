#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZBlobManager.generated.h"

UCLASS()
class XYZ_API UXYZBlobManager : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TSet<class UXYZBlob*> ActiveBlobs;
    int32 NextBlobId;

    void AddBlob(class UXYZBlob* Blob);
    void RemoveInactiveBlobs();
    void ProcessBlobs();
    void QueueAction(class UXYZAction* Action);
};