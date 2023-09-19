#include "XYZFollowAction.h"
#include "XYZActor.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZFollowAction::ProcessAction(TSet<AXYZActor*> Agents) {
    if (!TargetActor) return;
    for(AXYZActor* Actor : Agents){
        if (Actor && Actor->GetXYZAIController()) {
            if (TargetActor) {
                Actor->GetXYZAIController()->XYZFollowTarget(TargetActor);
            }
        }
    }
}
bool UXYZFollowAction::HasAgentComplete(class AXYZActor* Agent) {
    return Agent->State == EXYZUnitState::IDLE;
}