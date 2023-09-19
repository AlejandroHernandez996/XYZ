#include "XYZInputManager.h"
#include "XYZAction.h"
#include "XYZGameState.h"
#include "XYZActionFactory.h"
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
    ExecuteInput(InputMessage);
}

void UXYZInputManager::ExecuteInput(const FXYZInputMessage& InputMessage)
{
    if (InputMessage.SelectedActors.Num() == 0) return;
    AXYZActor* TargetActor = XYZGameState->ActorsByUID.Contains(InputMessage.XYZTargetActor) ? XYZGameState->ActorsByUID[InputMessage.XYZTargetActor] : nullptr;
    UXYZAction* XYZAction = UXYZActionFactory::CreateAction(InputMessage.SelectedActors, TargetActor, InputMessage.TargetLocation, InputMessage.bQueueInput, InputMessage.InputType, InputIndex, XYZGameState);
    UXYZBlobManager* BlobManager = XYZGameState->GetWorld()->GetAuthGameMode<AXYZGameMode>()->BlobManager;
    if (XYZAction) {
        BlobManager->Actions.Add(XYZAction);
    }
    InputIndex++;
}