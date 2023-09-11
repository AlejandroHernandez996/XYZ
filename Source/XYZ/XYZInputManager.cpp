#include "XYZInputManager.h"
#include "XYZAction.h"
#include "XYZGameState.h"
#include "XYZActionFactory.h"
#include "XYZMoveAction.h"
#include "XYZGameMode.h"
#include "XYZBlobManager.h"
#include "XYZBlobFactory.h"
#include "XYZBlob.h"

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
    
    AXYZActor* FirstActor = XYZGameState->ActorsByUID.Contains(InputMessage.SelectedActors[0]) ? XYZGameState->ActorsByUID[InputMessage.SelectedActors[0]] : nullptr;
    AXYZActor* TargetActor = XYZGameState->ActorsByUID.Contains(InputMessage.XYZTargetActor) ? XYZGameState->ActorsByUID[InputMessage.XYZTargetActor] : nullptr;

    if (FirstActor && !TargetActor && InputMessage.InputType == EXYZInputType::SECONDARY_INPUT) {
        UXYZAction* XYZAction = UXYZActionFactory::CreateAction(FirstActor, TargetActor, InputMessage.TargetLocation, InputMessage.bQueueInput, InputMessage.InputType, InputIndex);
        for (int i = 0; i < InputMessage.SelectedActors.Num(); i++) {
            XYZAction->ActorSet.Add(XYZGameState->ActorsByUID[InputMessage.SelectedActors[i]]);
        }
        UXYZBlob* Blob = UXYZBlobFactory::CreateBlobFromAction(XYZAction);
        Blob->Action = XYZAction;
        Blob->AgentsInBlob = XYZAction->ActorSet;
        XYZGameState->GetWorld()->GetAuthGameMode<AXYZGameMode>()->BlobManager->AddBlob(Blob);
        return;
    }

    for (auto UActorId : InputMessage.SelectedActors) {

        if (InputMessage.XYZTargetActor == UActorId) continue;
        AXYZActor* SelectedActor = XYZGameState->ActorsByUID.Contains(UActorId) ? XYZGameState->ActorsByUID[UActorId] : nullptr;
        if (!SelectedActor) continue;
        UXYZAction* XYZAction = UXYZActionFactory::CreateAction(SelectedActor, TargetActor, InputMessage.TargetLocation, InputMessage.bQueueInput, InputMessage.InputType, InputIndex);
        InputIndex++;
        SelectedActor->QueueAction(XYZAction);
    }
    FString messageString = InputMessage.ToString();
}