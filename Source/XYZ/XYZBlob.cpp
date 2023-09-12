#include "XYZBlob.h"

void UXYZBlob::ProcessBlob()
{
}

void UXYZBlob::FindCenterAgent() {
    if (AgentsInBlob.IsEmpty()) return;
    TArray<AXYZActor*> SortedAgents = AgentsInBlob.Array();
    Algo::Sort(SortedAgents, [this](AXYZActor* A, AXYZActor* B) {
        float DistanceA = FVector::DistSquared(A->GetActorLocation(), InitialCenter);
        float DistanceB = FVector::DistSquared(B->GetActorLocation(), InitialCenter);
        return DistanceA < DistanceB;
        });

    CenterAgent = SortedAgents[0];
}

void UXYZBlob::FindInitialCenterLocation() {
    InitialCenter = FVector::ZeroVector;
    for (AXYZActor* Actor : AgentsInBlob)
    {
        InitialCenter += Actor->GetActorLocation();
    }
    InitialCenter /= AgentsInBlob.Num();
}

