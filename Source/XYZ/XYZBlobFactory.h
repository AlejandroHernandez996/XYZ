#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZAction.h"
#include "XYZBlob.h"
#include "XYZBlobFactory.generated.h"

UCLASS()
class XYZ_API UXYZBlobFactory : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        static UXYZBlob* CreateBlobFromAction(const UXYZAction* Action, int32 BlobId);
};