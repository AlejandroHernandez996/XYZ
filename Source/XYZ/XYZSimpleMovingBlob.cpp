#include "XYZSimpleMovingBlob.h"
#include "XYZActor.h"
#include "XYZAction.h"
#include "CoreMinimal.h"
#include "XYZUnitState.h"
#include "XYZAIController.h"

void UXYZSimpleMovingBlob::ProcessBlob()
{
    if (ActionQueue.IsEmpty() || AgentsInBlob.IsEmpty()) return;
    if (CenterAgent && CenterAgent->State == EXYZUnitState::MOVING && !bOverrideBlob) return;
    bOverrideBlob = false;
    UXYZAction* ActionToProcess;
    ActionQueue.Dequeue(ActionToProcess);
    UE_LOG(LogTemp, Warning, TEXT("DeEnqueued Action"));
    if (!ActionToProcess) return;
    TargetLocation = ActionToProcess->TargetLocation;

    FindInitialCenterLocation();
    FindCenterAgent();

    FVector MinBounds = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector MaxBounds = FVector(FLT_MIN, FLT_MIN, FLT_MIN);
    for (AXYZActor* Actor : AgentsInBlob)
    {
        FVector Location = Actor->GetActorLocation();
        MinBounds = MinBounds.ComponentMin(Location);
        MaxBounds = MaxBounds.ComponentMax(Location);
        Actor->State = EXYZUnitState::MOVING;
    }

    float Area = (MaxBounds.X - MinBounds.X) * (MaxBounds.Y - MinBounds.Y);
    float Density = (float)AgentsInBlob.Num() / Area;

    if (Density < 0.000040f)
    {
        TArray<AXYZActor*> SortedAgents = AgentsInBlob.Array();
        Algo::Sort(SortedAgents, [this](AXYZActor* A, AXYZActor* B) {
            float DistanceA = FVector::DistSquared(A->GetActorLocation(), InitialCenter);
            float DistanceB = FVector::DistSquared(B->GetActorLocation(), InitialCenter);
            return DistanceA < DistanceB;
            });
        TSharedPtr<FAgentPack> AgentPack = MakeShared<FAgentPack>();
        FillPack(AgentPack.Get(), SortedAgents, 0);
        MovePack(AgentPack.Get(), 0);
    }
    else {
        for (AXYZActor* Actor : AgentsInBlob)
        {
            FVector ActorLocation = Actor->GetActorLocation();
            FVector DirectonFromCenter = ActorLocation - InitialCenter;
            FVector AgentTargetLocation = TargetLocation + DirectonFromCenter;
            Actor->GetController<AXYZAIController>()->XYZMoveToLocation(AgentTargetLocation);
        }
    }
    
    
}

void UXYZSimpleMovingBlob::FillPack(FAgentPack* AgentPack, TArray<AXYZActor*>& SortedAgents, int32 LayerIndex) {
    int32 LayerNodes = AgentPack->GetLayerNodeCount(LayerIndex);
    AgentPack->SetSectorDirections(LayerNodes);
    for (int i = 0; i < AgentPack->SectorDirections.Num(); i++) {
        if (SortedAgents.IsEmpty()) {
            return;
        }
        CurrentTargetLocation = TargetLocation + AgentPack->DISTANCE_FROM_AGENT * LayerIndex * AgentPack->SectorDirections[i];
        Algo::Sort(SortedAgents, [this](AXYZActor* A, AXYZActor* B) {
            float DistanceA = FVector::DistSquared(A->GetActorLocation(), CurrentTargetLocation);
            float DistanceB = FVector::DistSquared(B->GetActorLocation(), CurrentTargetLocation);
            return DistanceA < DistanceB;
            });
        AgentPack->Agents.Add(SortedAgents[0]);
        SortedAgents.RemoveAt(0);
        SortedAgentIndex++;
    }
    
    AgentPack->NextPack = MakeShared<FAgentPack>();
    FillPack(AgentPack->NextPack.Get(), SortedAgents, LayerIndex + 1);

}
void UXYZSimpleMovingBlob::MovePack(FAgentPack* AgentPack, int32 Level) {
    if (!AgentPack)return;
    if (AgentPack->Agents.Num() == 0) {
        return;
    }
    for (int i = 0; i < AgentPack->Agents.Num(); i++) {
        if (AgentPack->Agents[i]) {
            AgentPack->Agents[i]->GetController<AXYZAIController>()->XYZMoveToLocation(TargetLocation + AgentPack->DISTANCE_FROM_AGENT * Level * AgentPack->SectorDirections[i]);
        }
    }
    MovePack(AgentPack->NextPack.Get(), Level + 1);
}

