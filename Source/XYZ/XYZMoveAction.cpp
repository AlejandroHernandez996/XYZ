#include "XYZMoveAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "XYZGameMode.h"
#include "XYZMapManager.h"

void UXYZMoveAction::ProcessAction(TSet<AXYZActor*> Agents)
{
    FVector CenterLocation = FindInitialCenterLocation(Agents);
    AXYZActor* CenterAgent = FindCenterAgent(Agents, CenterLocation);

    FVector MinBounds = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector MaxBounds = FVector(FLT_MIN, FLT_MIN, FLT_MIN);
    for (AXYZActor* Actor : Agents)
    {
        if(Actor)
        {
            FVector Location = Actor->GetActorLocation();
            MinBounds = MinBounds.ComponentMin(Location);
            MaxBounds = MaxBounds.ComponentMax(Location);
        }
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
        MovePack(AgentPack, 0, false);
    }
    else {
        for (AXYZActor* Actor : Agents)
        {
            if(Actor)
            {
                FVector ActorLocation = Actor->GetActorLocation();
                FVector DirectonFromCenter = ActorLocation - CenterLocation;
                FVector AgentTargetLocation = TargetLocation + DirectonFromCenter;
                Actor->GetController<AXYZAIController>()->XYZMoveToLocation(AgentTargetLocation); 
            }
            
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
        FVector CurrentTargetLocation = TargetLocation + SortedAgents[0]->CurrentCapsuleRadius * LayerIndex * AgentPack->SectorDirections[i];
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
void UXYZMoveAction::MovePack(TSharedPtr<FAgentPack> AgentPack, int32 Level, bool bIsAttackMove) {
    if (!AgentPack)return;
    
    if (AgentPack->Agents.Num() == 0) {
        return;
    }
    for (int i = 0; i < AgentPack->Agents.Num(); i++) {
        AXYZActor* Agent = AgentPack->Agents[i];
        if (Agent) {
            FVector PackTargetLocation = TargetLocation + Agent->CurrentCapsuleRadius * Level * AgentPack->SectorDirections[i];
            UXYZMapManager* MapManager = Agent->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;

            FGridCell TargetCell = MapManager->Grid[MapManager->GetGridCoordinate(TargetLocation)];
            FGridCell PackTargetCell = MapManager->Grid[MapManager->GetGridCoordinate(PackTargetLocation)];
            
            if (bIsAttackMove) {
                if(TargetCell.Height == PackTargetCell.Height)
                {
                    Agent->GetController<AXYZAIController>()->XYZAttackMoveToLocation(PackTargetLocation);
                    Agent->TargetLocation = TargetLocation + Agent->CurrentCapsuleRadius * Level * AgentPack->SectorDirections[i];
                }else
                {
                    Agent->GetController<AXYZAIController>()->XYZAttackMoveToLocation(TargetLocation);
                    Agent->TargetLocation = TargetLocation;
                }
            }
            else {
                if(TargetCell.Height == PackTargetCell.Height)
                {
                    Agent->GetController<AXYZAIController>()->XYZMoveToLocation(PackTargetLocation);
                    Agent->TargetLocation = TargetLocation + Agent->CurrentCapsuleRadius * Level * AgentPack->SectorDirections[i];
                }else
                {
                    Agent->GetController<AXYZAIController>()->XYZMoveToLocation(TargetLocation);
                    Agent->TargetLocation = TargetLocation;
                }
            }
        }
    }
    MovePack(AgentPack->NextPack, Level + 1, bIsAttackMove);
}

bool UXYZMoveAction::HasAgentComplete(AXYZActor* Agent) {

    if(Agent)
    {
        return Agent->State == EXYZUnitState::IDLE;
    }
    return true;
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
        if(Actor)
        {
            Center += Actor->GetActorLocation();
        }
    }
    return Center /= Agents.Num();
}