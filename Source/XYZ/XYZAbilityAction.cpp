#include "XYZAbilityAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "XYZTargetAreaAbility.h"

void UXYZAbilityAction::ProcessAction(TSet<AXYZActor*> Agents) {
    AXYZActor* AbilityUser = nullptr;
    float ClosestDistance = MAX_FLT;
    for (AXYZActor* Actor : Agents) {
        if(ActorsInUse.Contains(Actor) || FinishedActors.Contains(Actor)) continue;
        if (Actor && Actor->ActorId == ActiveActorId && Actor->CanUseAbility()) {
            UXYZAbility* Ability = Actor->Abilities[AbilityIndex];
            if(Ability)
            {
                float Distance = FVector2D::Distance(FVector2D(Actor->GetActorLocation().X, Actor->GetActorLocation().Y), FVector2D(TargetLocation.X, TargetLocation.Y));
                if(Ability->IsA(UXYZTargetAreaAbility::StaticClass()))
                {
                    if((!AbilityUser || AbilityUser->Energy < Actor->Energy) && Distance < ClosestDistance)
                    {
                        AbilityUser = Actor;
                        ClosestDistance = Distance;
                    }
                }else
                {
                    ActorsInUse.Add(Actor);
                }
            }
        }else
        {
            FinishedActors.Add(Actor);
        }
    }
    if(AbilityUser)
    {
        ActorsInUse.Add(AbilityUser);
    }

    for(AXYZActor* Actor : ActorsInUse)
    {
        if(!Actor->Abilities.IsValidIndex(AbilityIndex)) continue;
        UXYZAbility* Ability = Actor->Abilities[AbilityIndex];
        if(!Ability) continue;
        float Distance = FVector2D::Distance(FVector2D(Actor->GetActorLocation().X, Actor->GetActorLocation().Y), FVector2D(TargetLocation.X, TargetLocation.Y));
        if(Actor->CastRange == -1 || Distance <= Actor->CastRange || Ability->CastRange == -1)
        {
            Actor->Abilities[AbilityIndex]->TargetLocation = TargetLocation;
            Actor->UseAbility(AbilityIndex);
            if(!Ability->bCanCastWhileMoving)
            {
                Actor->GetXYZAIController()->XYZStopMovement();
            }
            FinishedActors.Add(Actor);
        }else
        {
            Actor->GetXYZAIController()->XYZMoveToLocation(TargetLocation);
        }
    }
    ActorsInUse = ActorsInUse.Difference(FinishedActors);
}
bool UXYZAbilityAction::HasAgentComplete(class AXYZActor* Agent) {
    return FinishedActors.Contains(Agent);
}