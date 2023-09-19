#include "XYZAttackAction.h"
#include "XYZActor.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZAttackAction::ProcessAction(TSet<AXYZActor*> Agents) {

    for (AXYZActor* Actor : Agents)
    {
        if (Actor && Actor->GetXYZAIController()) {

            if (TargetActor) {
                Actor->GetXYZAIController()->XYZAttackMoveToTarget(TargetActor);
            }
            else {
                Actor->GetXYZAIController()->XYZAttackMoveToLocation(TargetLocation);
            }
       }
    }
}
bool UXYZAttackAction::HasAgentComplete(class AXYZActor* Agent) {
	return Agent->State == EXYZUnitState::IDLE;
}