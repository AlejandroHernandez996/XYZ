#pragma once

#include "CoreMinimal.h"
#include "XYZInputMessage.h" 
#include "XYZInputManager.generated.h"

UCLASS()
class XYZ_API UXYZInputManager : public UObject
{
    GENERATED_BODY()

public:
    UXYZInputManager();

    UFUNCTION()
    void QueueInput(const FXYZInputMessage& InputMessage);
    UFUNCTION()
    void ExecuteInput(const FXYZInputMessage& InputMessage);
    UFUNCTION()
    void ProcessInputs();
    
    UPROPERTY()
    int32 InputIndex = 0;
    UPROPERTY()
    class AXYZGameState* XYZGameState;
    UPROPERTY()
    TArray<FXYZInputMessage> InputQueue;
    UPROPERTY()
    int32 InputQueueIndex = 0;
};

