#include "XYZMoveAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "XYZBuilding.h"
#include "XYZGameMode.h"
#include "XYZMapManager.h"
#include "XYZMoveBatcher.h"

void UXYZMoveAction::ProcessAction(TSet<AXYZActor*> UnfilteredAgents)
{
    TSet<AXYZActor*> Agents;
    AgentsWithGroup.Empty();
    AgentGroups.Empty();
    for(AXYZActor* Actor : UnfilteredAgents)
    {
        if(!Actor) continue;
        if(AgentsWithGroup.Contains(Actor) || CompletedAgents.Contains(Actor)) continue;
        UXYZMoveBatcher* MoveBatcher = Actor->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MoveBatcher;

        AXYZBuilding* Building = Cast<AXYZBuilding>(Actor);
        if(Building || Actor->bIsFlying)
        {
            //Actor->GetXYZAIController()->XYZMoveToLocation(TargetLocation);
            TSharedPtr<FXYZMove> Move = MakeShared<FXYZMove>();
            Move->TargetLocation = TargetLocation;
            Move->ActorToMove = Actor;
            MoveBatcher->MovesToProcess.Add(Move);
            CompletedAgents.Add(Actor);
        }
        else
        {
            Agents.Add(Actor);
        }
    }

    CreateAgentGroups(Agents);
    for(TSharedPtr<FAgentGroup> AgentGroup : AgentGroups)
    {
        if(!AgentGroup->bIsMoving)
        {
            MoveGroup(AgentGroup);
            AgentGroup->bIsMoving = true;
        }
    }
    /**
    FVector CenterLocation = FindInitialCenterLocation(Agents);
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
        for(AXYZActor* Actor : Agents)
        {
            if(CompletedAgents.Contains(Actor) || !Actor) continue;
            Actor->GetController<AXYZAIController>()->XYZMoveToLocation(TargetLocation);
        }
        /*TArray<AXYZActor*> SortedAgents = Agents.Array();
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
                if(CompletedAgents.Contains(Actor)) continue;
                FVector ActorLocation = Actor->GetActorLocation();
                FVector DirectonFromCenter = ActorLocation - CenterLocation;
                FVector AgentTargetLocation = TargetLocation + DirectonFromCenter;
                Actor->GetController<AXYZAIController>()->XYZMoveToLocation(AgentTargetLocation); 
            }
            
        }
    }
    **/
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

            TSharedPtr<FGridCell> TargetCell = MapManager->Grid[MapManager->GetGridCoordinate(TargetLocation)];
            TSharedPtr<FGridCell> PackTargetCell = MapManager->Grid[MapManager->GetGridCoordinate(PackTargetLocation)];
            
            if (bIsAttackMove) {
                if(TargetCell->Height == PackTargetCell->Height)
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
                if(TargetCell->Height == PackTargetCell->Height)
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

void UXYZMoveAction::CreateAgentGroups(TSet<AXYZActor*> Agents)
{
    if(Agents.IsEmpty()) return;
    TSet<FIntVector2> SearchedCoords;

    for (AXYZActor* Agent : Agents)
    {
        if (!AgentsWithGroup.Contains(Agent) && !CompletedAgents.Contains(Agent))
        {
            UXYZMapManager* MapManager = Agent->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
            TSharedPtr<FAgentGroup> AgentGroup = MakeShared<FAgentGroup>();
            AgentGroups.Add(AgentGroup);
            TSet<AXYZActor*> ActorsToAdd;
            ActorsToAdd.Add(Agent);
            
            FindAndAddNeighbors(MapManager, Agent, AgentGroup, SearchedCoords, ActorsToAdd, Agents);
            
            FVector CenterLocation = FindInitialCenterLocation(AgentGroup->AgentsInGroup);
            AgentGroup->CenterAgent = FindCenterAgent(AgentGroup->AgentsInGroup,CenterLocation);
            CalculateDensityForGroup(AgentGroup);
        }
    }
}

void UXYZMoveAction::FindAndAddNeighbors(UXYZMapManager* MapManager,
    AXYZActor* Agent,
    TSharedPtr<FAgentGroup> AgentGroup,
    TSet<FIntVector2>& SearchedCoords,
    TSet<AXYZActor*>& ActorsToAdd,
    TSet<AXYZActor*>& AgentsInAction)
{
    AgentGroup->AgentsInGroup.Add(Agent);
    AgentsWithGroup.Add(Agent,AgentGroup);
    FIntVector2 AgentGridCoord = Agent->GridCoord;
    TSet<FIntVector2> CoordsToSearch = MapManager->GetPerimeterCoords(AgentGridCoord, FIntVector2(1, 1));

    for (FIntVector2 Coord : CoordsToSearch)
    {
        if (!SearchedCoords.Contains(Coord))
        {
            SearchedCoords.Add(Coord);
            if (MapManager->Grid.Contains(Coord))
            {
                TSharedPtr<FGridCell> GridCell = MapManager->Grid[Coord];
                TSet<AXYZActor*> ActorsInCell = GridCell->ActorsInCell;

                for (AXYZActor* ActorInCell : ActorsInCell)
                {
                    if (ActorInCell != Agent &&
                        !ActorsToAdd.Contains(ActorInCell) &&
                        !AgentGroup->AgentsInGroup.Contains(ActorInCell) &&
                        AgentsInAction.Contains(ActorInCell))
                    {
                        ActorsToAdd.Add(ActorInCell);
                        FindAndAddNeighbors(MapManager, ActorInCell, AgentGroup, SearchedCoords, ActorsToAdd, AgentsInAction);
                    }
                }
            }
        }
    }
}

void UXYZMoveAction::CalculateDensityForGroup(TSharedPtr<FAgentGroup> AgentGroup)
{
    FVector MinBounds = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector MaxBounds = FVector(FLT_MIN, FLT_MIN, FLT_MIN);
    for (AXYZActor* AgentInGroup :AgentGroup->AgentsInGroup)
    {
        if(AgentInGroup)
        {
            FVector Location = AgentInGroup->GetActorLocation();
            MinBounds = MinBounds.ComponentMin(Location);
            MaxBounds = MaxBounds.ComponentMax(Location);
        }
    }
    float Area = (MaxBounds.X - MinBounds.X) * (MaxBounds.Y - MinBounds.Y);
    AgentGroup->Density = (float)AgentGroup->AgentsInGroup.Num() / Area;
}

void UXYZMoveAction::MoveGroup(TSharedPtr<FAgentGroup> AgentGroup)
{
    for (AXYZActor* Agent : AgentGroup->AgentsInGroup)
    {
        if(Agent)
        {
            FVector ActorLocation = Agent->GetActorLocation();
            FVector DirectonFromCenter = ActorLocation - AgentGroup->CenterAgent->GetActorLocation();
            FVector AgentTargetLocation = TargetLocation + DirectonFromCenter;

            UXYZMapManager* MapManager = Agent->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
            FIntVector2 TargetGridCoord = MapManager->GetGridCoordinate(TargetLocation);
            FIntVector2 AgentTargetGridCoord = MapManager->GetGridCoordinate(AgentTargetLocation);
            UXYZMoveBatcher* MoveBatcher = Agent->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MoveBatcher;

            if(MapManager->Grid.Contains(TargetGridCoord) &&
                MapManager->Grid.Contains(AgentTargetGridCoord) &&
                MapManager->Grid[AgentTargetGridCoord]->Height == MapManager->Grid[TargetGridCoord]->Height)
            {
                TSharedPtr<FXYZMove> Move = MakeShared<FXYZMove>();
                Move->TargetLocation = AgentTargetLocation;
                Move->ActorToMove = Agent;
                MoveBatcher->MovesToProcess.Add(Move);
                //Agent->GetController<AXYZAIController>()->XYZMoveToLocation(AgentTargetLocation); 
            }else
            {
                TSharedPtr<FXYZMove> Move = MakeShared<FXYZMove>();
                Move->TargetLocation = TargetLocation;
                Move->ActorToMove = Agent;
                MoveBatcher->MovesToProcess.Add(Move);
                //Agent->GetController<AXYZAIController>()->XYZMoveToLocation(TargetLocation); 
            }
        }
            
    }
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

bool UXYZMoveAction::HasAgentComplete(AXYZActor* Agent) {

    if(Agent && AgentsWithGroup.Contains(Agent))
    {
        if(Agent->bIsFlying && Agent->State == EXYZUnitState::IDLE)
        {
            return true;
        }
        if(Agent->bIsFlying)
        {
            return false;
        }
        return AgentsWithGroup[Agent]->CenterAgent->State == EXYZUnitState::IDLE;
    }
    return false;
}

bool UXYZMoveAction::IsGroupComplete(TSharedPtr<FAgentGroup> AgentGroup)
{
    if(AgentGroup && AgentGroup->CenterAgent)
    {
        return AgentGroup->CenterAgent->State == EXYZUnitState::IDLE;
    }
    return false;
}