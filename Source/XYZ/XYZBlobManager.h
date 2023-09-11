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
    TMap<int32, class UXYZBlob*> ActiveBlobs;
    int32 NextBlobId;

    void AddBlob(class UXYZBlob* Blob);
    void ProcessBlobs();
};