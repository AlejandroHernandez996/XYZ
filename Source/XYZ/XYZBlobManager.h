#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "XYZBlobManager.generated.h"

UCLASS()
class XYZ_API UXYZBlobManager : public UObject, public IProcessable
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TSet<class UXYZBlob*> ActiveBlobs;
    UPROPERTY()
    int32 NextBlobId;
    UPROPERTY()
        TArray<class UXYZAction*> Actions;
    int32 ActionIndex = 0;
    UFUNCTION()
    void AddBlob(class UXYZBlob* Blob);
    UFUNCTION()
    void RemoveInactiveBlobs();
    void Process(float DeltaSeconds);
    UFUNCTION()
    void QueueAction(class UXYZAction* Action);
};