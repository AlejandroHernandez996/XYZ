// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAction.h"
#include "XYZActor.h"

AXYZActor* UXYZAction::FindCenterAgent(TSet<AXYZActor*> Agents, FVector CenterLocation) {
    if (Agents.IsEmpty()) return nullptr;
    TArray<AXYZActor*> SortedAgents = Agents.Array();
    Algo::Sort(SortedAgents, [this, CenterLocation](AXYZActor* A, AXYZActor* B) {
        float DistanceA = FVector::DistSquared(A->GetActorLocation(), CenterLocation);
        float DistanceB = FVector::DistSquared(B->GetActorLocation(), CenterLocation);
        return DistanceA < DistanceB;
        });

    return SortedAgents[0];
}

FVector UXYZAction::FindInitialCenterLocation(TSet<AXYZActor*> Agents) {
    FVector Center = FVector::ZeroVector;
    for (AXYZActor* Actor : Agents)
    {
        Center += Actor->GetActorLocation();
    }
    return Center /= Agents.Num();
}