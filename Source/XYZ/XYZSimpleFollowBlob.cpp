#include "XYZSimpleFollowBlob.h"
#include "XYZActor.h"
#include "XYZAction.h"
#include "CoreMinimal.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZSimpleFollowBlob::ProcessBlob()
{
    if (ActionQueue.IsEmpty() || AgentsInBlob.IsEmpty()) return;
    if (CenterAgent && CenterAgent->State == EXYZUnitState::FOLLOWING && !bOverrideBlob) return;
    FindInitialCenterLocation();
    FindCenterAgent();
    bOverrideBlob = false;
    UXYZAction* ActionToProcess;
    ActionQueue.Dequeue(ActionToProcess);
    if (!ActionToProcess || !ActionToProcess->TargetActor) return;
    for (AXYZActor* Actor : AgentsInBlob)
    {
        Actor->GetController<AXYZAIController>()->XYZFollowTarget(ActionToProcess->TargetActor);
    }
}