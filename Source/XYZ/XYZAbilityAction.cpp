#include "XYZAbilityAction.h"
#include "XYZActor.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZAbilityAction::ProcessAction(TSet<AXYZActor*> Agents) {
    for (AXYZActor* Actor : Agents) {
        if (Actor && Actor->ActorId == ActiveActorId) {
            Actor->UseAbility(AbilityIndex);
        }
    }
}
bool UXYZAbilityAction::HasAgentComplete(class AXYZActor* Agent) {
    return true;
}