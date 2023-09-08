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

    void QueueInput(const FXYZInputMessage& InputMessage);
    void DequeueInput();
    void ExecuteInput(const FXYZInputMessage& InputMessage);
    void HandleInputs();
    int32 InputIndex = 0;

    UPROPERTY()
    class AXYZGameState* XYZGameState;
    
};