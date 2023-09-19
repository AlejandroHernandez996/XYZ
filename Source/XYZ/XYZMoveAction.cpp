#include "XYZMoveAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZMoveAction::ProcessAction(TSet<AXYZActor*> Agents)
{
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
        MovePack(AgentPack, 0);
    }
    else {
        for (AXYZActor* Actor : Agents)
        {
            FVector ActorLocation = Actor->GetActorLocation();
            FVector DirectonFromCenter = ActorLocation - CenterLocation;
            FVector AgentTargetLocation = TargetLocation + DirectonFromCenter;
            Actor->GetController<AXYZAIController>()->XYZMoveToLocation(AgentTargetLocation);
        }
    }

}

void UXYZMoveAction::FillPack(TSharedPtr<FAgentPack> AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex) {
    int32 LayerNodes = AgentPack->GetLayerNodeCount(LayerIndex);
    AgentPack->SetSectorDirections(LayerNodes);
    for (int i = 0; i < AgentPack->SectorDirections.Num(); i++) {
        if (SortedAgents.IsEmpty()) {
            return;
        }
        FVector CurrentTargetLocation = TargetLocation + AgentPack->DISTANCE_FROM_AGENT * LayerIndex * AgentPack->SectorDirections[i];
        Algo::Sort(SortedAgents, [this, CurrentTargetLocation](AXYZActor* A, AXYZActor* B) {
            float DistanceA = FVector::DistSquared(A->GetActorLocation(), CurrentTargetLocation);
            float DistanceB = FVector::DistSquared(B->GetActorLocation(), CurrentTargetLocation);
            return DistanceA < DistanceB;
            });
        AgentPack->Agents.Add(SortedAgents[0]);
        SortedAgents.RemoveAt(0);
    }

    AgentPack->NextPack = MakeShared<FAgentPack>();
    FillPack(AgentPack->NextPack, SortedAgents, LayerIndex + 1);

}
void UXYZMoveAction::MovePack(TSharedPtr<FAgentPack> AgentPack, int32 Level) {
    if (!AgentPack)return;
    if (AgentPack->Agents.Num() == 0) {
        return;
    }
    for (int i = 0; i < AgentPack->Agents.Num(); i++) {
        if (AgentPack->Agents[i]) {
            AgentPack->Agents[i]->TargetLocation = TargetLocation + AgentPack->DISTANCE_FROM_AGENT * Level * AgentPack->SectorDirections[i];
            AgentPack->Agents[i]->GetController<AXYZAIController>()->XYZMoveToLocation(TargetLocation + AgentPack->DISTANCE_FROM_AGENT * Level * AgentPack->SectorDirections[i]);
        }
    }
    MovePack(AgentPack->NextPack, Level + 1);
}

bool UXYZMoveAction::HasAgentComplete(AXYZActor* Agent) {

    return Agent->State == EXYZUnitState::IDLE;
}

AXYZActor* UXYZMoveAction::FindCenterAgent(TSet<AXYZActor*> Agents, FVector CenterLocation) {
    if (Agents.IsEmpty()) return nullptr;
    TArray<AXYZActor*> SortedAgents = Agents.Array();
    Algo::Sort(SortedAgents, [this, CenterLocation](AXYZActor* A, AXYZActor* B) {
        float DistanceA = FVector::DistSquared(A->GetActorLocation(), CenterLocation);
        float DistanceB = FVector::DistSquared(B->GetActorLocation(), CenterLocation);
        return DistanceA < DistanceB;
        });

    return SortedAgents[0];
}

FVector UXYZMoveAction::FindInitialCenterLocation(TSet<AXYZActor*> Agents) {
    FVector Center = FVector::ZeroVector;
    for (AXYZActor* Actor : Agents)
    {
        Center += Actor->GetActorLocation();
    }
    return Center /= Agents.Num();
}