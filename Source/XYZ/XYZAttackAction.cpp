#include "XYZAttackAction.h"
#include "XYZActor.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZAttackAction::ProcessAction(TSet<AXYZActor*> Agents) {

    if (TargetActor) {
        for (AXYZActor* Actor : Agents)
        {
            if (Actor && Actor->GetXYZAIController()) {

             Actor->GetXYZAIController()->XYZAttackMoveToTarget(TargetActor);
              
            }
        }
        return;
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
bool UXYZAttackAction::HasAgentComplete(class AXYZActor* Agent) {
	return Agent->State == EXYZUnitState::IDLE;
}