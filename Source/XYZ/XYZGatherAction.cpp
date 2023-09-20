#include "XYZGatherAction.h"
#include "XYZActor.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"
#include "XYZResourceActor.h"
#include "XYZWorker.h"

void UXYZGatherAction::ProcessAction(TSet<AXYZActor*> Agents) {
    if (!TargetActor && !TargetActor->IsA(AXYZResourceActor::StaticClass())) return;
    for (AXYZActor* Actor : Agents) {
        if (Actor && Actor->GetXYZAIController()) {
            if (Actor->IsA(AXYZWorker::StaticClass())) {
                Actor->GetXYZAIController()->XYZGatherResource(Cast<AXYZResourceActor>(TargetActor));
            }
            else {
                Actor->GetXYZAIController()->XYZMoveToActor(TargetActor);
            }
        }
    }
}
bool UXYZGatherAction::HasAgentComplete(class AXYZActor* Agent) {
    return Agent->State == EXYZUnitState::IDLE;
}