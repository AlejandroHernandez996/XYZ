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

    if(!HasAuthority() &&  bShowRallyPoint && bCanRally)
    {
        ULineBatchComponent* LineBatcher = GetWorld()->ForegroundLineBatcher;

        FVector StartLocation = GetActorLocation();
        StartLocation.Z += GetCapsuleComponent()->GetScaledCapsuleHalfHeight()/2.0f;
        FVector EndLocation = RallyPoint;
        FColor DebugColor = FColor::Orange;
        
        if (LineBatcher)
        {
            LineBatcher->DrawLine(EndLocation, StartLocation, DebugColor, 0, 3.0f, .1f);
        }
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
            if(!BuildingAbility->IsA(UXYZUpgradeAbility::StaticClass()))
            {
                bCanRally = true;
            }
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
    DOREPLIFETIME(AXYZBuilding, BuildQueueId);
    DOREPLIFETIME(AXYZBuilding, bIsTraining);
}

void AXYZBuilding::ProcessBuildQueue(float DeltaTime) {
    if(CancelProductionIndex != -1)
    {
        CancelProductionAtIndex();
    }
    if (BuildQueue.IsEmpty()) return;

    UXYZBuildingAbility* CurrentAbility = BuildQueue[0];
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
            if(HasValidSpawnPoint())
            {
                TrainUnit(CurrentAbility->UnitTemplate);
            }else
            {
                return;
            }
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
    bShowRallyPoint = bShowDecal && bCanRally;
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
        bool bIsAtMaxUpgrade = CurrentUpgradedStage >= UpgradeAbility->MaxStage;
        if(GameMode->UpgradeManager->ContainsUpgrade(UpgradeAbility) && bIsAtMaxUpgrade) return;
    }
    if(UpgradeAbility)
    {
        GameMode->UpgradeManager->AddUpgradeToResearch(UpgradeAbility);
    }
    if (BuildQueueNum < MAX_BUILD_QUEUE_SIZE && 
        GameState->MineralsByTeamId[TeamId] - BuildingAbility->MineralCost >= 0) {
        GameState->MineralsByTeamId[TeamId] -= BuildingAbility->MineralCost;
        BuildQueue.Add(BuildingAbility);
        BuildQueueId.Add(BuildingAbility->ID);
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

    FVector SpawnLocation = ValidSpawnPoint;
    FVector Start = SpawnLocation + FVector(0, 0, 1000);
    FVector End = SpawnLocation - FVector(0, 0, 10000); 

    FHitResult HitResult;

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic);

    if (bHit)
    {
        SpawnLocation.Z = HitResult.Location.Z;
    }
    
    AXYZActor* SpawnActor = GetWorld()->SpawnActor<AXYZActor>(UnitTemplate, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if(bIsFlying)
    {
        FVector FlyingSpawnLocation = GetActorLocation();
        FlyingSpawnLocation.Z = SpawnActor->FlyingZOffset;
        SpawnActor->SetActorLocation(FlyingSpawnLocation);
    }
    SpawnActor->TeamId = TeamId;
    GetWorld()->GetGameState<AXYZGameState>()->SupplyByTeamId[SpawnActor->TeamId + 2] += SpawnActor->SupplyGain;
    GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->AddActorServer(SpawnActor);

    UXYZBuildingAbility* CurrentAbility = BuildQueue[0];
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

bool AXYZBuilding::HasValidSpawnPoint()
{
    UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
    TArray<FIntVector2> PerimeterCoords = MapManager->GetPerimeterCoords(GridCoord, FIntVector2(GridSize.X, GridSize.Y));

    FIntVector2 ClosestValidPerimeterCoord;
    FIntVector2 SpawnPointToGridCoord = MapManager->GetGridCoordinate(SpawnPoint);
    FIntVector2 RallyPointToGridCoord = MapManager->GetGridCoordinate(RallyPoint);

    int32 ClosestDistance = INT_MAX;
    for(FIntVector2 PerimeterCoord : PerimeterCoords)
    {
        if(!MapManager->IsCoordOccupiedByBuilding(PerimeterCoord))
        {
            int32 DistanceToSpawnPoint = FVector2D::Distance(FVector2D(PerimeterCoord.X, PerimeterCoord.Y), FVector2D(SpawnPointToGridCoord.X, SpawnPointToGridCoord.Y));
            int32 DistanceToRallyPoint = FVector2D::Distance(FVector2D(PerimeterCoord.X, PerimeterCoord.Y), FVector2D(RallyPointToGridCoord.X, RallyPointToGridCoord.Y));
            int32 Distance = RallyPoint == SpawnPoint ? DistanceToSpawnPoint : DistanceToRallyPoint;
            if(Distance < ClosestDistance && MapManager->AreGridCoordsSameHeight(PerimeterCoord, GridCoord))
            {
                ClosestDistance = Distance;
                ClosestValidPerimeterCoord = PerimeterCoord;
            }
        }
    }
    if(ClosestDistance != INT_MAX)
    {
        ValidSpawnPoint = MapManager->GridCoordToWorldCoord(ClosestValidPerimeterCoord);
        return true;
    }
    return false;
}

void AXYZBuilding::CancelProduction() {
    if (BuildQueue.IsEmpty()) return;
    UXYZBuildingAbility* CurrentAbility = BuildQueue[0];
    BuildQueue.RemoveAt(0);
    BuildQueueId.RemoveAt(0);
    TimeToBuild = -1.0f;
    TotalBuildTime = -1.0f;
    BuildQueueNum--;
    bIsTraining = false;

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

void AXYZBuilding::CancelProductionAtIndex()
{
    if(CancelProductionIndex == -1 || BuildQueue.IsEmpty() || !BuildQueue.IsValidIndex(CancelProductionIndex)) return;
    if(CancelProductionIndex == 0)
    {
        BuildQueue[0]->bCanCancel = true;
        CancelProduction();
    }else
    {
        GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->MineralsByTeamId[TeamId] += BuildQueue[CancelProductionIndex]->MineralCost;
        UXYZUpgradeAbility* UpgradeAbility = Cast<UXYZUpgradeAbility>(BuildQueue[CancelProductionIndex]);
        if(UpgradeAbility)
        {
            GetWorld()->GetAuthGameMode<AXYZGameMode>()->UpgradeManager->RemoveUpgradeFromResearch(UpgradeAbility);
        }
        BuildQueue.RemoveAt(CancelProductionIndex);
        BuildQueueId.RemoveAt(CancelProductionIndex);
        BuildQueueNum--;
    }
    CancelProductionIndex = -1;
}
void AXYZBuilding::Process(float DeltaTime)
{
    Super::Process(DeltaTime);

    UXYZUpgradeManager* UpgradeManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->UpgradeManager;
    for(UXYZAbility* Ability : Abilities)
    {
        if(!Ability) continue;;
        UXYZUpgradeAbility* UpgradeAbility = Cast<UXYZUpgradeAbility>(Ability);
        if(!UpgradeAbility) continue;
        if(UpgradeManager->UpgradesByTeam[TeamId].Contains(UpgradeAbility->ID) && UpgradeAbility->CurrentStage < UpgradeManager->UpgradesByTeam[TeamId][UpgradeAbility->ID]->CurrentStage)
        {
            UpgradeAbility->CurrentStage = UpgradeManager->UpgradesByTeam[TeamId][UpgradeAbility->ID]->CurrentStage;
        }
    }
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
        if(BuildQueue[0])
        {
            BuildQueue[0]->bCanCancel = true;
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

