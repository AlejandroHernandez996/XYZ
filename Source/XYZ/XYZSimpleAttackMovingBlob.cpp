// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZSimpleAttackMovingBlob.h"
#include "XYZAIController.h"

void UXYZSimpleAttackMovingBlob::MovePack(FAgentPack* AgentPack, int32 Level) {
    if (!AgentPack)return;
    if (AgentPack->Agents.Num() == 0) {
        return;
    }
    for (int i = 0; i < AgentPack->Agents.Num(); i++) {
        if (AgentPack->Agents[i]) {
            FVector AgentTargetLocation = TargetLocation + AgentPack->DISTANCE_FROM_AGENT;
            AgentPack->Agents[i]->TargetLocation = AgentTargetLocation;
            AgentPack->Agents[i]->GetController<AXYZAIController>()->XYZAttackMoveToLocation(AgentTargetLocation * Level * AgentPack->SectorDirections[i]);
        }
    }
    MovePack(AgentPack->NextPack.Get(), Level + 1);
}