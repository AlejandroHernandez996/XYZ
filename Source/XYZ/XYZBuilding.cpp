// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuilding.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "XYZBuildingAbility.h"
#include "XYZGameState.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"

void AXYZBuilding::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (GetLocalRole() != ROLE_Authority) {
        return;
    }
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
    for (UXYZAbility* Ability : Abilities) {
        UXYZBuildingAbility* BuildingAbility = Cast<UXYZBuildingAbility>(Ability);
        if (BuildingAbility) {
            BuildingAbility->OwningBuilding = this;
        }
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
    if (TimeToBuild == -1.0f) {
        TotalBuildTime = CurrentAbility->BuildTime;
        TimeToBuild = 0.0f;
    }
    else if (TimeToBuild >= TotalBuildTime) {
        TrainUnit(CurrentAbility->UnitTemplate);
        CancelProduction();
        return;
    }
    TimeToBuild += DeltaTime;
}

void AXYZBuilding::EnqueueAbility(UXYZBuildingAbility* BuildingAbility) {
    AXYZGameState* GameState = GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>();
    if (BuildQueueNum < MAX_BUILD_QUEUE_SIZE && GameState->MineralsByTeamId[TeamId] - BuildingAbility->MineralCost >= 0) {
        GameState->MineralsByTeamId[TeamId] -= BuildingAbility->MineralCost;
        BuildQueue.Enqueue(BuildingAbility);
        BuildQueueNum++;
    }
}

void AXYZBuilding::TrainUnit(TSubclassOf<class AXYZActor> UnitTemplate) {
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    FVector SpawnLocation = SpawnPoint;

    AXYZActor* SpawnActor = GetWorld()->SpawnActor<AXYZActor>(UnitTemplate, SpawnLocation, SpawnPoint.Rotation(), SpawnParams);
    SpawnActor->TeamId = TeamId;
    GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->ActorIndex++;
    SpawnActor->UActorId = GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->ActorIndex;

    UXYZBuildingAbility* CurrentAbility = *BuildQueue.Peek();
    CurrentAbility->bCanCancel = false;
}

void AXYZBuilding::CancelProduction() {
    if (BuildQueue.IsEmpty()) return;
    UXYZBuildingAbility* CurrentAbility = *BuildQueue.Peek();
    BuildQueue.Pop();
    TimeToBuild = -1.0f;
    TotalBuildTime = -1.0f;
    BuildQueueNum--;
    if (CurrentAbility->bCanCancel) {
        GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->MineralsByTeamId[TeamId] += CurrentAbility->MineralCost;
    }
    CurrentAbility->bCanCancel = true;
}