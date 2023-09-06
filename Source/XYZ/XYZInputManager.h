#pragma once

#include "CoreMinimal.h"
#include "XYZInputMessage.h" // Include this for FInputMessage struct
#include "XYZInputManager.generated.h"

UCLASS()
class XYZ_API UXYZInputManager : public UObject
{
    GENERATED_BODY()

public:
    UXYZInputManager();

    void QueueInput(const FXYZInputMessage& InputMessage);
    void DequeueInput();

    // You can add more helper functions here

protected:
    // Override this function if you want the manager to do something every frame
    virtual void Tick(float DeltaTime);

private:
    TQueue<FXYZInputMessage> InputQueue; // The actual input queue using TQueue

    void ExecuteInput(const FXYZInputMessage& InputMessage); // Executes an input message
};