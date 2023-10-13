// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuilding.h"
#include "Engine.h"
#include "SoundTypes.h"
#include "Net/UnrealNetwork.h"
#include "XYZBuildingAbility.h"
#include "XYZGameState.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "XYZAIController.h"
#include "XYZActorCache.h"

void AXYZBuilding::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if(bIsSpawned && BuildingSpawnLocation != GetActorLocation())
    {
        SetActorLocation(BuildingSpawnLocation);
    }
}

void AXYZBuilding::BeginPlay() {
    Super::BeginPlay();
    UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
    if (CapsuleComp)
    {
        float CapsuleRadius = CapsuleComp->GetScaledCapsuleRadius();
        FVector ForwardVector = GetActorForwardVector();
        SpawnPoint = GetActorLocation() + (ForwardVector * CapsuleRadius* 2.0f);
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
    DOREPLIFETIME(AXYZBuilding, bIsSpawned);
    DOREPLIFETIME(AXYZBuilding, BuildingSpawnLocation);
}

void AXYZBuilding::ProcessBuildQueue(float DeltaTime) {
    if (BuildQueue.IsEmpty()) return;

    UXYZBuildingAbility* CurrentAbility = *BuildQueue.Peek();
    if (!CurrentAbility) {
        CancelProduction();
        return;
    }

    AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();
    if (!GameState) return;
    int32 CurrentSupply = GameState->SupplyByTeamId[TeamId];
    int32 MaxSupply = GameState->SupplyByTeamId[TeamId + 2];

    bool bIsSupplyReserved = GameState->ReservedSupplyByBuilding[TeamId].Contains(UActorId);

    if (!bIsTraining) {
        bIsTraining = true;
        TimeToBuild = 0.0f;
        TotalBuildTime = CurrentAbility->BuildTime;
        
    }

    if (!bIsSupplyReserved && CurrentSupply + CurrentAbility->SupplyCost <= MaxSupply) {
        GameState->ReservedSupplyByBuilding[TeamId].Add(UActorId, CurrentAbility->SupplyCost);
        GameState->SupplyByTeamId[TeamId] += CurrentAbility->SupplyCost;
    }

    // IF OVERCAPPED AND IS RESERVING REMOVE RESERVE AND SUBTRACT FROM SUPPLY ALSO RESET TRAINING
    if (CurrentSupply > MaxSupply && bIsSupplyReserved) {
        TimeToBuild = 0.0f;
        GameState->ReservedSupplyByBuilding[TeamId].Remove(UActorId);
        GameState->SupplyByTeamId[TeamId + 2] -= CurrentAbility->SupplyCost;
        return;
    }

    // CURRENT SUPPLY + SUPPLY COST >= MAX RESET BUILD TIME
    if (CurrentSupply > MaxSupply && !bIsSupplyReserved) {
        TimeToBuild = 0.0f;
        return;
    }

    if (TimeToBuild >= TotalBuildTime) {
        TrainUnit(CurrentAbility->UnitTemplate);
        CancelProduction();
        return;
    }

    if (bIsSupplyReserved) {
        TimeToBuild += DeltaTime;
    }
}

void AXYZBuilding::EnqueueAbility(UXYZBuildingAbility* BuildingAbility) {
    if(BuildingState != EXYZBuildingState::BUILT) return;
    
    AXYZGameState* GameState = GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>();
    AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();

    if (BuildQueueNum < MAX_BUILD_QUEUE_SIZE && 
        GameState->MineralsByTeamId[TeamId] - BuildingAbility->MineralCost >= 0) {
        GameState->MineralsByTeamId[TeamId] -= BuildingAbility->MineralCost;
        BuildQueue.Enqueue(BuildingAbility);
        BuildQueueNum++;
        if(GameState->SupplyByTeamId[TeamId] + BuildingAbility->SupplyCost > GameState->SupplyByTeamId[TeamId+2])
        {
            GameMode->TeamIdToPlayerController[TeamId]->PlaySound(ESoundTypes::SUPPLY);
        }
    }
}

void AXYZBuilding::TrainUnit(TSubclassOf<class AXYZActor> UnitTemplate) {
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
    FVector MyActorLocation = GetActorLocation(); 
    
    if(RallyPoint != SpawnPoint)
    {
        FVector DirectionToRallyPoint = RallyPoint - MyActorLocation; 
        DirectionToRallyPoint.Normalize();
        SpawnPoint = GetActorLocation() + (DirectionToRallyPoint * CapsuleRadius* 2.0f);
    }
    if(RallyTarget)
    {
        FVector DirectionToRallyTarget = RallyTarget->GetActorLocation() - MyActorLocation;
        DirectionToRallyTarget.Normalize();
        SpawnPoint = GetActorLocation() + (DirectionToRallyTarget * CapsuleRadius* 2.0f);
    }
    FVector SpawnLocation = SpawnPoint;
    FVector Start = SpawnLocation + FVector(0, 0, 1000); // Start 1000 units above
    FVector End = SpawnLocation - FVector(0, 0, 10000);   // End 1000 units below

    FHitResult HitResult;

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic); // You can change the collision channel as per your requirement

    if (bHit)
    {
        SpawnLocation.Z = HitResult.Location.Z;
    }
    
    AXYZActor* SpawnActor = GetWorld()->SpawnActor<AXYZActor>(UnitTemplate, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    SpawnActor->TeamId = TeamId;
    GetWorld()->GetGameState<AXYZGameState>()->SupplyByTeamId[SpawnActor->TeamId + 2] += SpawnActor->SupplyGain;
    GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->AddActorServer(SpawnActor);

    UXYZBuildingAbility* CurrentAbility = *BuildQueue.Peek();
    CurrentAbility->bCanCancel = false;

    if (RallyTarget) {
        if (RallyTarget->TeamId == 2) {
            SpawnActor->GetXYZAIController()->XYZMoveToActor(RallyTarget);
        }
        else if (RallyTarget->TeamId == TeamId) {
            SpawnActor->GetXYZAIController()->XYZFollowTarget(RallyTarget);
        }
        else {
            SpawnActor->GetXYZAIController()->XYZAttackMoveToTarget(RallyTarget);
        }
    }
    else if (SpawnPoint != RallyPoint) {
        SpawnActor->GetXYZAIController()->XYZMoveToLocation(RallyPoint);
    }
    bIsTraining = false;
}

void AXYZBuilding::CancelProduction() {
    if (BuildQueue.IsEmpty()) return;
    UXYZBuildingAbility* CurrentAbility = *BuildQueue.Peek();
    BuildQueue.Pop();
    TimeToBuild = -1.0f;
    TotalBuildTime = -1.0f;
    BuildQueueNum--;

    int32 CurrentSupply = GetWorld()->GetGameState<AXYZGameState>()->SupplyByTeamId[TeamId];
    int32 MaxSupply = GetWorld()->GetGameState<AXYZGameState>()->SupplyByTeamId[TeamId + 2];
    bool bIsSupplyReserved = GetWorld()->GetGameState<AXYZGameState>()->ReservedSupplyByBuilding[TeamId].Contains(UActorId);

    if (CurrentAbility->bCanCancel) {
        GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->MineralsByTeamId[TeamId] += CurrentAbility->MineralCost;
        if (bIsSupplyReserved) {
            GetWorld()->GetGameState<AXYZGameState>()->SupplyByTeamId[TeamId] -= CurrentAbility->SupplyCost;
        }
    }
    if (bIsSupplyReserved) {
        GetWorld()->GetGameState<AXYZGameState>()->ReservedSupplyByBuilding[TeamId].Remove(UActorId);
    }

    CurrentAbility->bCanCancel = true;
}

void AXYZBuilding::Process(float DeltaTime)
{
    Super::Process(DeltaTime);
    switch (BuildingState) {
    case EXYZBuildingState::PLACED:
        BuildingState = EXYZBuildingState::BUILDING;
        break;
    case EXYZBuildingState::BUILDING:
        if(TimeToBuild >= TotalBuildTime)
        {
            BuildingState = EXYZBuildingState::BUILT;
            GetWorld()->GetGameState<AXYZGameState>()->SupplyByTeamId[TeamId + 2] += SupplyGain;
            UXYZActorCache* ActorCache = GetWorld()->GetAuthGameMode<AXYZGameMode>()->ActorCache;
            if(ActorCache)
            {
                ActorCache->AddActorCount(TeamId, ActorId);
            }
        }else
        {
            Build(DeltaTime);
        }
        break;
    case EXYZBuildingState::BUILT:
        ProcessBuildQueue(GetWorld()->DeltaTimeSeconds);
        break;
    default: ;
    }
}

void AXYZBuilding::Build(float DeltaTime)
{
    TimeToBuild += DeltaTime;
    float TickPercentageBuilt = DeltaTime/TotalBuildTime;
    float TickBuildHealth = MaxHealth * TickPercentageBuilt;
    Health = FMath::Clamp(Health+TickBuildHealth,0.0f, MaxHealth);
}

