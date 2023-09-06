#include "XYZInputManager.h"

UXYZInputManager::UXYZInputManager()
{
    // Constructor implementation here, if needed
}

void UXYZInputManager::QueueInput(const FXYZInputMessage& InputMessage)
{
    InputQueue.Enqueue(InputMessage);
}

void UXYZInputManager::DequeueInput()
{
    FXYZInputMessage InputMessage;
    if (InputQueue.Dequeue(InputMessage))
    {
        ExecuteInput(InputMessage);
    }
}

void UXYZInputManager::ExecuteInput(const FXYZInputMessage& InputMessage)
{
    FString messageString = InputMessage.ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s"), *messageString);
}

void UXYZInputManager::Tick(float DeltaTime)
{
    // Process all the inputs in the queue
    while (!InputQueue.IsEmpty())
    {
        DequeueInput();
    }
}