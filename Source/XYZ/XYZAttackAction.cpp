#include "XYZAttackAction.h"
#include "XYZActor.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"
#include "XYZBuilding.h"

void UXYZAttackAction::ProcessAction(TSet<AXYZActor*> Agents)
{
    if(bHasTargetActor) return;
    if(TargetActor)
    {
        bHasTargetActor = true;
    }
    Super::ProcessAction(Agents);
    
}

/**
void UXYZAttackAction::ProcessAction(TSet<AXYZActor*> UnfilteredAgents)
{
    if (TargetActor) {
        for (AXYZActor* Actor : UnfilteredAgents)
        {
            if (Actor && Actor->GetXYZAIController()) {

                Actor->GetXYZAIController()->XYZAttackMoveToTarget(TargetActor);
              
            }
        }
        return;
    }
    TSet<AXYZActor*> Agents;

    for(AXYZActor* Actor : UnfilteredAgents)
    {
        AXYZBuilding* Building = Cast<AXYZBuilding>(Actor);
        if(Building || Actor->bIsFlying)
        {
            Actor->GetXYZAIController()->XYZAttackMoveToLocation(TargetLocation);
        }
        else
        {
            Agents.Add(Actor);
        }
    }
    
    FVector CenterLocation = FindInitialCenterLocation(Agents);
    AXYZActor* CenterAgent = FindCenterAgent(Agents, CenterLocation);

    FVector MinBounds = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector MaxBounds = FVector(FLT_MIN, FLT_MIN, FLT_MIN);
    for (AXYZActor* Actor : Agents)
    {
        FVector Location = Actor->GetActorLocation();
        MinBounds = MinBounds.ComponentMin(Location);
        MaxBounds = MaxBounds.ComponentMax(Location);
    }

    float Area = (MaxBounds.X - MinBounds.X) * (MaxBounds.Y - MinBounds.Y);
    float Density = (float)Agents.Num() / Area;

    if (Density < 0.000040f)
    {
        TArray<AXYZActor*> SortedAgents = Agents.Array();
        Algo::Sort(SortedAgents, [this, CenterLocation](AXYZActor* A, AXYZActor* B) {
            float DistanceA = FVector::DistSquared(A->GetActorLocation(), CenterLocation);
            float DistanceB = FVector::DistSquared(B->GetActorLocation(), CenterLocation);
            return DistanceA < DistanceB;
            });
        TSharedPtr<FAgentPack> AgentPack = MakeShared<FAgentPack>();
        FillPack(AgentPack, SortedAgents, 0);
        MovePack(AgentPack, 0, true);
    }
    else {
        for (AXYZActor* Actor : Agents)
        {
            FVector ActorLocation = Actor->GetActorLocation();
            FVector DirectonFromCenter = ActorLocation - CenterLocation;
            FVector AgentTargetLocation = TargetLocation + DirectonFromCenter;
            Actor->GetController<AXYZAIController>()->XYZAttackMoveToLocation(AgentTargetLocation);
        }
    }
}
*/
bool UXYZAttackAction::HasAgentComplete(class AXYZActor* Agent) {
    if(bHasTargetActor)
    {
        if(!TargetActor || !Agent->TargetActor || Agent->State == EXYZUnitState::IDLE)
        {
            return true;
        }
        return false;
    }
	return Agent->State == EXYZUnitState::IDLE;
}