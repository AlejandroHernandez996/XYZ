// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuilding.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "XYZBuildingAbility.h"

void AXYZBuilding::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    ProcessBuildQueue(DeltaTime);
}

void AXYZBuilding::BeginPlay() {
    Super::BeginPlay();
    UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
    if (CapsuleComp)
    {
        float CapsuleRadius = CapsuleComp->GetScaledCapsuleRadius();
        FVector ForwardVector = GetActorForwardVector();
        SpawnPoint = GetActorLocation() + (ForwardVector * CapsuleRadius* 1.5f);
        RallyPoint = SpawnPoint;
    }
}

void AXYZBuilding::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AXYZBuilding, RallyPoint);
    DOREPLIFETIME(AXYZBuilding, SpawnPoint);
    DOREPLIFETIME(AXYZBuilding, TotalBuildTime);
    DOREPLIFETIME(AXYZBuilding, TimeToBuild);
    DOREPLIFETIME(AXYZBuilding, BuildQueueNum);
}

void AXYZBuilding::ProcessBuildQueue(float DeltaTime) {
    if (BuildQueue.IsEmpty()) return;

    UXYZBuildingAbility* CurrentAbility = *BuildQueue.Peek();
    if (!CurrentAbility) {
        CancelProduction();
        return;
    }
    if (TimeToBuild == 0.0f) {
        TotalBuildTime = CurrentAbility->BuildTime;
    }
    else if (TimeToBuild == TotalBuildTime) {
        TrainUnit(CurrentAbility->UnitTemplate);
        CancelProduction();
        return;
    }
    TimeToBuild += DeltaTime;
}

void AXYZBuilding::EnqueueAbility(UXYZBuildingAbility* BuildingAbility) {
    if (BuildQueueNum < MAX_BUILD_QUEUE_SIZE) {
        BuildQueue.Enqueue(BuildingAbility);
        BuildQueueNum++;
    }
}

void AXYZBuilding::TrainUnit(TSubclassOf<class AXYZActor> UnitTemplate) {
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    FVector SpawnLocation = SpawnPoint;

    // Spawn the actor.
    AXYZActor* SpawnActor = GetWorld()->SpawnActor<AXYZActor>(UnitTemplate, SpawnLocation, SpawnPoint.Rotation(), SpawnParams);
    SpawnActor->TeamId = TeamId;
}

void AXYZBuilding::CancelProduction() {
    if (BuildQueue.IsEmpty()) return;
    BuildQueue.Pop();
    TimeToBuild = 0.0f;
    TotalBuildTime = 0.0f;
}