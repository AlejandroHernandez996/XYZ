#include "XYZInputManager.h"
#include "XYZAction.h"
#include "XYZGameState.h"
#include "XYZActionFactory.h"

UXYZInputManager::UXYZInputManager()
{
    InputIndex = 0;
}

void UXYZInputManager::QueueInput(const FXYZInputMessage& InputMessage)
{
    //InputQueue.Enqueue(InputMessage);
    ExecuteInput(InputMessage);
}

void UXYZInputManager::ExecuteInput(const FXYZInputMessage& InputMessage)
{
    if (!XYZGameState) return;
    
    for (auto UActorId : InputMessage.SelectedActors) {

        AXYZActor* SelectedActor = XYZGameState->ActorsByUID.Contains(UActorId) ? XYZGameState->ActorsByUID[UActorId] : nullptr;
        if (!SelectedActor) return;
        AXYZActor* TargetActor = XYZGameState->ActorsByUID.Contains(InputMessage.XYZTargetActor) ? XYZGameState->ActorsByUID[InputMessage.XYZTargetActor] : nullptr;
        UXYZAction* XYZAction = UXYZActionFactory::CreateAction(SelectedActor, TargetActor, InputMessage.TargetLocation, InputMessage.bQueueInput, InputMessage.InputType, InputIndex);
        InputIndex++;
        if (XYZAction) {
            SelectedActor->QueueAction(XYZAction);
        }
    }
    FString messageString = InputMessage.ToString();
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *messageString);
}

void UXYZInputManager::HandleInputs()
{
    //TArray<FXYZInputMessage> InputQueueCopy = InputQueue;
    //if (InputQueueCopy.IsEmpty() || InputIndex == InputQueueCopy.Num()) return;
    //for (; InputIndex < InputQueueCopy.Num();InputIndex++) {
   // }
}