#include "XYZAbilityAction.h"
#include "XYZActor.h"
#include "XYZTargetAreaAbility.h"

void UXYZAbilityAction::ProcessAction(TSet<AXYZActor*> Agents) {
    AXYZActor* AbilityUser = nullptr;
    for (AXYZActor* Actor : Agents) {
        if (Actor && Actor->ActorId == ActiveActorId && Actor->CanUseAbility()) {
            UXYZAbility* Ability = Actor->Abilities[AbilityIndex];
            if(Ability)
            {
                if(Ability->IsA(UXYZTargetAreaAbility::StaticClass()))
                {
                    if(!AbilityUser || AbilityUser->Energy < Actor->Energy)
                    {
                        AbilityUser = Actor;
                    }
                }else
                {
                    Actor->Abilities[AbilityIndex]->TargetLocation = TargetLocation;
                    Actor->UseAbility(AbilityIndex);
                }
                
            }
        }
    }
    if(AbilityUser != nullptr)
    {
        AbilityUser->Abilities[AbilityIndex]->TargetLocation = TargetLocation;
        AbilityUser->UseAbility(AbilityIndex);
    }
}
bool UXYZAbilityAction::HasAgentComplete(class AXYZActor* Agent) {
    return true;
}