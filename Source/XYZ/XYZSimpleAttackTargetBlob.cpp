#include "XYZSimpleAttackTargetBlob.h"
#include "XYZActor.h"
#include "XYZAction.h"
#include "CoreMinimal.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZSimpleAttackTargetBlob::ProcessBlob()
{
    if (ActionQueue.IsEmpty() || AgentsInBlob.IsEmpty()) return;
    if (CenterAgent && CenterAgent->State == EXYZUnitState::ATTACK_MOVING && !bOverrideBlob) return;
    FindInitialCenterLocation();
    FindCenterAgent();
    bOverrideBlob = false;
    UXYZAction* ActionToProcess;
    ActionQueue.Dequeue(ActionToProcess);
    if (!ActionToProcess || !ActionToProcess->TargetActor) return;
    for (AXYZActor* Actor : AgentsInBlob)
    {
        Actor->GetController<AXYZAIController>()->XYZAttackMoveToTarget(ActionToProcess->TargetActor);
    }
}