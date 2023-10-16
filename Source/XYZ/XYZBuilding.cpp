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
#include "XYZMapManager.h"
#include "XYZUpgradeAbility.h"
#include "XYZUpgradeManager.h"

AXYZBuilding::AXYZBuilding() : Super()
{
}

void AXYZBuilding::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if(bIsSpawned && BuildingSpawnLocation != GetActorLocation())
    {
        SetActorLocation(BuildingSpawnLocation);
    }

    if(GetWorld()->GetGameState<AXYZGameState>())
    {
        AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();
        for(UXYZAbility* Ability : Abilities)
        {
            UXYZUpgradeAbility* UpgradeAbility = Cast<UXYZUpgradeAbility>(Ability);
            if(!UpgradeAbility) continue;

            int32 CurrentStage = GameState->UpgradeAbilitiesResearched.GetCurrentUpgradeStage(UpgradeAbility->ID, TeamId);
            if(CurrentStage == UpgradeAbility->CurrentStage)
            {
                UpgradeAbility->UpdateStage(CurrentStage+1);
            }
            
        }
    }

    if(HasAuthority() && bCanRally)
    {
        if(RallyTarget)
        {
            RallyPoint = RallyTarget->GetActorLocation();
        }
    }

    if(!HasAuthority() && bShowRallyPoint)
    {
        float LifeTime = .1f;
        bool bPersistentLines = false;
        bool bDepthIsForeground = (0 == SDPG_Foreground);

        ULineBatchComponent* LineBatcher = (GetWorld() ? (bDepthIsForeground ? GetWorld() ->ForegroundLineBatcher : (( bPersistentLines || (LifeTime > 0.f) ) ? GetWorld() ->PersistentLineBatcher : GetWorld() ->LineBatcher)) : nullptr);

        if (LineBatcher)
            LineBatcher->DrawLine(GetActorLocation(), RallyPoint, FColor::Orange, 0, 1.0f, DeltaTime);
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
            bCanRally = true;
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
        UXYZUpgradeAbility* UpgradeAbility = Cast<UXYZUpgradeAbility>(CurrentAbility);
        if(UpgradeAbility)
        {
            ResearchUpgrade(UpgradeAbility);
        }else
        {
            TrainUnit(CurrentAbility->UnitTemplate);
        }
        bIsTraining = false;
        CancelProduction();
        return;
    }

    if (bIsSupplyReserved) {
        TimeToBuild += DeltaTime;
    }
}

void AXYZBuilding::ShowDecal(bool bShowDecal, EXYZDecalType DecalType)
{
    Super::ShowDecal(bShowDecal, DecalType);
    if(bCanRally)
    {
        bShowRallyPoint = !bShowDecal && RallyPoint != SpawnPoint;
    }
}

void AXYZBuilding::BuildingAttack()
{
    FVector ActorLocation = GetActorLocation();
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    if (TargetActor &&
        TargetActor != this &&
        TargetActor->State != EXYZUnitState::DEAD)
    {
        FVector TargetActorLocation = TargetActor->GetActorLocation();
        float TargetActorRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius();

        FVector Direction = TargetActorLocation - ActorLocation;
        Direction.Z = 0;
        Direction.Normalize();

        FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);
    
        DistanceToTarget -= TargetActorRadius;
        if (DistanceToTarget <= AttackRange)
        {
            Attack();
        }
    }
    else
    {
        TargetActor = nullptr;
    }

}

void AXYZBuilding::EnqueueAbility(UXYZBuildingAbility* BuildingAbility) {
    if(BuildingState != EXYZBuildingState::BUILT) return;
    
    AXYZGameState* GameState = GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>();
    AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();

    UXYZUpgradeAbility* UpgradeAbility = Cast<UXYZUpgradeAbility>(BuildingAbility);
    if(UpgradeAbility)
    {
        UpgradeAbility->TeamId = TeamId;
    }
    if(UpgradeAbility)
    {
        if(GameMode->UpgradeManager->IsUpgradeBeingResearched(UpgradeAbility)) return;
        int32 CurrentUpgradedStage = GameState->UpgradeAbilitiesResearched.GetCurrentUpgradeStage(UpgradeAbility->ID, TeamId);
        bool bIsAtMaxUpgrade = CurrentUpgradedStage == UpgradeAbility->MaxStage;
        if(GameMode->UpgradeManager->ContainsUpgrade(UpgradeAbility) && bIsAtMaxUpgrade) return;
    }
    if(UpgradeAbility)
    {
        GameMode->UpgradeManager->AddUpgradeToResearch(UpgradeAbility);
    }
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
}

void AXYZBuilding::ResearchUpgrade(UXYZUpgradeAbility* UpgradeAbility)
{
    UXYZUpgradeManager* UpgradeManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->UpgradeManager;
    UpgradeManager->AddUpgradeAbility(UpgradeAbility);
    UpgradeAbility->bCanCancel = false;
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

    UXYZUpgradeAbility* UpgradeAbility = Cast<UXYZUpgradeAbility>(CurrentAbility);
    if(UpgradeAbility)
    {
        UXYZUpgradeManager* UpgradeManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->UpgradeManager;
        UpgradeManager->RemoveUpgradeFromResearch(UpgradeAbility);
    }
}

void AXYZBuilding::Process(float DeltaTime)
{
    Super::Process(DeltaTime);

    if(bCanAttack && BuildingState == EXYZBuildingState::BUILT)
    {
        if(TargetActor && !GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->DoesActorHasVisionOfActor(this, TargetActor))
        {
            TargetActor = nullptr;
        }
        if (!TargetActor || TargetActor->Health <= 0.0f)
        {
            TargetActor = FindClosestActor(true);
        }
        if (TargetActor)
        {
            BuildingAttack();
        }
    }
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

void AXYZBuilding::ClearProduction()
{
    while(!BuildQueue.IsEmpty())
    {
        if(*BuildQueue.Peek())
        {
            (*BuildQueue.Peek())->bCanCancel = true;
        }
        CancelProduction();
    }
}

void AXYZBuilding::Build(float DeltaTime)
{
    TimeToBuild += DeltaTime;
    float TickPercentageBuilt = DeltaTime/TotalBuildTime;
    float TickBuildHealth = MaxHealth * TickPercentageBuilt;
    Health = FMath::Clamp(Health+TickBuildHealth,0.0f, MaxHealth);
}

