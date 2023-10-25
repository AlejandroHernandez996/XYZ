// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZWorker.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "XYZBaseBuilding.h"
#include "XYZResourceActor.h"
#include "XYZAIController.h"
#include "Engine.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "XYZMapManager.h"
#include "XYZWorkerAbility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

void AXYZWorker::BeginPlay() {
    Super::BeginPlay();
    State = EXYZUnitState::GATHERING;

    for(UXYZAbility* Ability : Abilities)
    {
        UXYZWorkerAbility* WorkerAbility = Cast<UXYZWorkerAbility>(Ability);
        if(WorkerAbility)
        {
            WorkerAbility->OwningWorker = this;
        }
    }
}

void AXYZWorker::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
    if (SkeletalMeshComp)
    {
        SkeletalMeshComp->SetCollisionProfileName(CollisionName);
    }
    if (GetCapsuleComponent())
    {
        GetCapsuleComponent()->SetCollisionProfileName(CollisionName);
    }
    
}

void AXYZWorker::Process(float DeltaTime)
{
    Super::Process(DeltaTime);
    if(bIsFlying)
    {
        ProcessFlyingWorker(DeltaTime);
        return;
    }
    if(State == EXYZUnitState::PLACING)
    {
        ScanXYZActorsAhead();
        if(ActivePlacementAbility)
        {
            UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
            FVector PlacingLocation = ActivePlacementAbility->BuildingLocation;
            
            FIntVector2 CurrentGridPosition = GridCoord;
            FIntVector2 PlacementCenterGridPosition = MapManager->GetGridCoordinate(PlacingLocation);
            FIntVector2 PlacementGridSize = FIntVector2(ActivePlacementAbility->GridSize.X, ActivePlacementAbility->GridSize.Y);
            bool bHasSameHeightAsBuildingLocation = MapManager->Grid.Contains(CurrentGridPosition) &&
                MapManager->Grid.Contains(PlacementCenterGridPosition) &&
                MapManager->Grid[CurrentGridPosition]->Height == MapManager->Grid[PlacementCenterGridPosition]->Height;

            if(MapManager->DoesBuildingAreaOverlap(PlacementCenterGridPosition, PlacementGridSize))
            {
                SetState(EXYZUnitState::IDLE);
                return;
            }
            if(IsWorkerInDistanceToPlace(CurrentGridPosition, PlacementCenterGridPosition, PlacementGridSize) && bHasSameHeightAsBuildingLocation)
            {
                PlaceBuilding();
            }
            else if(XYZAIController)
            {
                TArray<FIntVector2> PerimeterTiles = MapManager->GetPerimeterCoords(PlacementCenterGridPosition, PlacementGridSize);
                bool bHasValidTileToPlace = false;
                for (const FIntVector2& Tile : PerimeterTiles) 
                {
                    if (MapManager->AreGridCoordsSameHeight(Tile, PlacementCenterGridPosition) && !MapManager->IsCoordOccupiedByBuilding(Tile)) 
                    {
                        FVector DestinationLocation = MapManager->GridCoordToWorldCoord(Tile);
                        XYZAIController->MoveToLocation(DestinationLocation,.001f);
                        bHasValidTileToPlace = true;
                        break;
                    }
                }
                if(!bHasValidTileToPlace)
                {
                    SetState(EXYZUnitState::IDLE);
                }
            }else
            {
                SetState(EXYZUnitState::IDLE);
            }
        }else
        {
            SetState(EXYZUnitState::IDLE);
        }
    }
    if(State == EXYZUnitState::BUILDING)
    {
        ActivePlacementAbility = nullptr;
        SetState(EXYZUnitState::IDLE);
    }
    if (State == EXYZUnitState::GATHERING) {
        bHasAvoidance = false;
        if (!TargetActor) {
            FindClosestResource();
        }
        if (TargetActor) {
            Gather();
        }
        else {
            GetXYZAIController()->XYZStopMovement();
        }
    }
    else if (State == EXYZUnitState::RETURNING) {
        bHasAvoidance = false;
        if (ClosestBase) {
            Return();
        }else
        {
            FindClosestBase();
        }
        if(!ClosestBase) {
            GetXYZAIController()->XYZStopMovement();
        }
    }
    else if (State == EXYZUnitState::MINING)
    {
        bHasAvoidance = false;
        AXYZResourceActor* Resource = Cast<AXYZResourceActor>(TargetActor);
        if(!Resource || !Resource->Workers.Contains(this))
        {
            SetState(EXYZUnitState::GATHERING);
        }
        else
        {
            if(HeldResource == Resource->ResourceType)
            {
                StartReturningResource();
            }
            else if(TimeToGather >= GatherRate)
            {
                TargetActor->Health = FMath::Clamp(TargetActor->Health - MiningAmountByResourceType[Resource->ResourceType], 0.0f, TargetActor->MaxHealth);
                TimeToGather = 0;
                StartReturningResource();
            }
            else
            {
                if(Resource->Workers[this])
                {
                    TimeToGather += DeltaTime;
                }
                else if(Resource->Workers.Num() < Resource->RESOURCE_CAPACITY)
                {
                    Resource->Workers[this] = true;
                }
                else
                {
                    Resource->RemoveWorker(this);
                    TargetActor = nullptr;
                    SetState(EXYZUnitState::GATHERING);
                }
            }
        }
        
    }
    else {
        GetCharacterMovement()->bUseRVOAvoidance = true;
    }
}

void AXYZWorker::Gather() {
    FVector ActorLocation = GetActorLocation() + GetActorForwardVector() * CurrentCapsuleRadius;
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    AXYZResourceActor* ResourceActor = Cast<AXYZResourceActor>(TargetActor);
    if (ResourceActor && TargetActor->Health > 0.0f) {

        UCapsuleComponent* CapsuleComp = TargetActor->GetCapsuleComponent();
        FVector ClosestPoint;
        CapsuleComp->GetClosestPointOnCollision(ActorLocation, ClosestPoint);

        FVector2D TargetLocation2D = FVector2D(ClosestPoint.X, ClosestPoint.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

        if (DistanceToTarget <= CurrentCapsuleRadius * 1.5f)
        {
            SetState(EXYZUnitState::MINING);
            ResourceActor->AddWorker(this);
            GetXYZAIController()->StopMovement();
        }
        else if(!bIsGatheringResource && !GetCharacterMovement()->IsMovementInProgress()){
            GetXYZAIController()->XYZGatherResource(Cast<AXYZResourceActor>(TargetActor));
        }
    }
    else {
        TargetActor = nullptr;
    }
}

void AXYZWorker::FlyingGather(float DeltaSeconds)
{
    FVector ActorLocation = GetActorLocation() + GetActorForwardVector() * CurrentCapsuleRadius;
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    AXYZResourceActor* ResourceActor = Cast<AXYZResourceActor>(TargetActor);
    if (ResourceActor && TargetActor->Health > 0.0f) {

        UCapsuleComponent* CapsuleComp = TargetActor->GetCapsuleComponent();
        FVector ClosestPoint;
        CapsuleComp->GetClosestPointOnCollision(ActorLocation, ClosestPoint);

        FVector2D TargetLocation2D = FVector2D(ClosestPoint.X, ClosestPoint.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

        if (DistanceToTarget <= CurrentCapsuleRadius * 2.0f)
        {
            SetState(EXYZUnitState::MINING);
            ResourceActor->AddWorker(this);
        }
        else if(!bIsGatheringResource){
            FVector GatherLocation = TargetActor->GetActorLocation();
            GatherLocation.Z = FlyingZOffset;
            FVector DirectionToTarget = (GatherLocation - GetActorLocation()).GetSafeNormal();
            FVector NewLocation = GetActorLocation() + DirectionToTarget * FlyingSpeed * DeltaSeconds;
            FRotator NewRotation = (GatherLocation - NewLocation).Rotation();
            SetActorLocation(NewLocation);
            SetActorRotation(NewRotation);
        }
    }
    else {
        TargetActor = nullptr;
    }
}

void AXYZWorker::FlyingReturn(float DeltaSeconds)
{
    FVector ActorLocation = GetActorLocation() + GetActorForwardVector() * CurrentCapsuleRadius;
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    if (ClosestBase && State == EXYZUnitState::RETURNING && HeldResource != EXYZResourceType::NONE) {
        UCapsuleComponent* CapsuleComp = ClosestBase->GetCapsuleComponent();
        FVector ClosestPoint;
        CapsuleComp->GetClosestPointOnCollision(ActorLocation, ClosestPoint);

        FVector2D TargetLocation2D = FVector2D(ClosestPoint.X, ClosestPoint.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

        if (DistanceToTarget <= CurrentCapsuleRadius*3.0f && HeldResource != EXYZResourceType::NONE)
        {
            if (HeldResource == EXYZResourceType::MINERAL) {
                GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->MineralsByTeamId[TeamId] += MiningAmountByResourceType[EXYZResourceType::MINERAL];
            }
            else {
                GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->GasByTeamId[TeamId] += MiningAmountByResourceType[EXYZResourceType::GAS];
            }
            if(!TargetActor)
            {
                FindClosestResource();
            }
            HeldResource = EXYZResourceType::NONE;
            if (TargetActor && TargetActor->IsA(AXYZResourceActor::StaticClass())) {
                GetXYZAIController()->XYZGatherResource(Cast<AXYZResourceActor>(TargetActor));
            }
            else {
                SetState(EXYZUnitState::IDLE);
                GetXYZAIController()->XYZStopMovement();
            }
        }else
        {
            FVector ReturnLocation = ClosestBase->GetActorLocation();
            ReturnLocation.Z = FlyingZOffset;
            FVector DirectionToTarget = (ReturnLocation - GetActorLocation()).GetSafeNormal();
            FVector NewLocation = GetActorLocation() + DirectionToTarget * FlyingSpeed * DeltaSeconds;
            FRotator NewRotation = (ReturnLocation - NewLocation).Rotation();
            SetActorLocation(NewLocation);
            SetActorRotation(NewRotation);
        }

    }
}

void AXYZWorker::StartReturningResource() {
    if (State == EXYZUnitState::MINING) {
        if(TargetActor && TargetActor->IsA(AXYZResourceActor::StaticClass()))
        {
            HeldResource = Cast<AXYZResourceActor>(TargetActor)->ResourceType;
            FindClosestBase();
            if (ClosestBase) {
                GetXYZAIController()->XYZReturnResource(ClosestBase);
            }
            else {
                SetState(EXYZUnitState::IDLE);
            }
        }else
        {
            SetState(EXYZUnitState::IDLE);
        }
       
    }
    bIsGatheringResource = false;
}
void AXYZWorker::Return() {
    FVector ActorLocation = GetActorLocation() + GetActorForwardVector() * CurrentCapsuleRadius;
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    if (ClosestBase && State == EXYZUnitState::RETURNING && HeldResource != EXYZResourceType::NONE) {
        UCapsuleComponent* CapsuleComp = ClosestBase->GetCapsuleComponent();
        FVector ClosestPoint;
        CapsuleComp->GetClosestPointOnCollision(ActorLocation, ClosestPoint);

        FVector2D TargetLocation2D = FVector2D(ClosestPoint.X, ClosestPoint.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

        if (DistanceToTarget <= CurrentCapsuleRadius*3.0f && HeldResource != EXYZResourceType::NONE)
        {
            if (HeldResource == EXYZResourceType::MINERAL) {
                GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->MineralsByTeamId[TeamId] += 5;
            }
            else {
                GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->GasByTeamId[TeamId] += 25;
            }
            if(!TargetActor)
            {
                FindClosestResource();
            }
            HeldResource = EXYZResourceType::NONE;
            if (TargetActor && TargetActor->IsA(AXYZResourceActor::StaticClass())) {
                GetXYZAIController()->XYZGatherResource(Cast<AXYZResourceActor>(TargetActor));
            }
            else {
                SetState(EXYZUnitState::IDLE);
                GetXYZAIController()->XYZStopMovement();
            }
        }

    }
}

void AXYZWorker::FindClosestBase()
{
    TArray<AActor*> FoundBases;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AXYZBaseBuilding::StaticClass(), FoundBases);

    AActor* ResultBase = nullptr;
    float ClosestDistance = FLT_MAX;

    for (AActor* Base : FoundBases)
    {
        AXYZBaseBuilding* BaseBuilding = Cast<AXYZBaseBuilding>(Base);
        if(!BaseBuilding || BaseBuilding->BuildingState != EXYZBuildingState::BUILT) continue;
        
        float Distance = FVector::Dist(Base->GetActorLocation(), GetActorLocation());
        if (Distance < ClosestDistance && Base->IsA(AXYZBaseBuilding::StaticClass()) && Cast<AXYZBaseBuilding>(Base)->TeamId == TeamId)
        {
            ClosestDistance = Distance;
            ResultBase = Base;
        }
    }

    ClosestBase = Cast<AXYZBaseBuilding>(ResultBase);
}

void AXYZWorker::FindClosestResource()
{
    TArray<AActor*> FoundResources;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AXYZResourceActor::StaticClass(), FoundResources);

    int32 SmallestCapacity = INT_MAX;
    float ClosestDistance = FLT_MAX;
    AXYZResourceActor* SmallestCapacityResource = nullptr;

    for (AActor* Resource : FoundResources)
    {
        float Distance = FVector::Dist(Resource->GetActorLocation(), GetActorLocation());
        AXYZResourceActor* ResourceActor = Cast<AXYZResourceActor>(Resource);
        if (ResourceActor)
        {
            if(ResourceActor->ResourceType != ResourceToGather)
            {
                continue;
            }
            if(ResourceActor->Workers.Num() < SmallestCapacity && (Distance < 1000.0f || ResourceActor->ResourceType == EXYZResourceType::GAS))
            {
                SmallestCapacityResource = ResourceActor;
                SmallestCapacity = ResourceActor->Workers.Num();
                ClosestDistance = Distance;
            }
            else if(ResourceActor->Workers.Num() == SmallestCapacity && Distance < ClosestDistance)
            {
                SmallestCapacityResource = ResourceActor;
                SmallestCapacity = ResourceActor->Workers.Num();
                ClosestDistance = Distance;
            }
        }
    }
    TargetActor = SmallestCapacityResource;
}

void AXYZWorker::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AXYZWorker, HeldResource);
}

void AXYZWorker::SetState(EXYZUnitState NewState)
{
    if(State == EXYZUnitState::PLACING)
    {
        XYZAIController->StopMovement();
    }
    if(State == EXYZUnitState::PLACING && NewState != EXYZUnitState::BUILDING && ActivePlacementAbility)
    {
        GetWorld()->GetGameState<AXYZGameState>()->MineralsByTeamId[TeamId] += ActivePlacementAbility->MineralCost;
        GetWorld()->GetGameState<AXYZGameState>()->GasByTeamId[TeamId] += ActivePlacementAbility->GasCost;
        ActivePlacementAbility = nullptr;
    }
    Super::SetState(NewState);
}

void AXYZWorker::PlaceBuilding()
{
    if(ActivePlacementAbility)
    {
        FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ActivePlacementAbility->BuildingLocation);
        FRotator CurrentRotation = GetActorRotation();
        CurrentRotation.Pitch = LookAtRotation.Pitch;
        CurrentRotation.Yaw = LookAtRotation.Yaw;
        SetActorRotation(CurrentRotation);
    
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        UXYZMapManager* MapManager = GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager;
        FVector SpawnLocation = ActivePlacementAbility->BuildingLocation;
        SpawnLocation.Z = MapManager->Grid[MapManager->GetGridCoordinate(SpawnLocation)]->Height;

        AXYZBuilding* SpawnActor = GetWorld()->SpawnActor<AXYZBuilding>(ActivePlacementAbility->BuildingTemplate, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        SpawnActor->TeamId = TeamId;
        GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->AddActorServer(SpawnActor);
        FVector OffsetLocation = SpawnLocation;
        OffsetLocation.Z += SpawnActor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

        SpawnActor->TotalBuildTime = ActivePlacementAbility->BuildTime;
        SpawnActor->SetActorLocation(OffsetLocation);
        SpawnActor->BuildingSpawnLocation = OffsetLocation;
        SpawnActor->bIsSpawned = true;
        SpawnActor->BuildingState = EXYZBuildingState::PLACED;
        SpawnActor->Health = 5.0f;
        
        GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->AddToUpdateSet(SpawnActor);
        
        ActivePlacementAbility = nullptr;
        SetState(EXYZUnitState::BUILDING);
    }else
    {
        SetState(EXYZUnitState::IDLE);
    }
    
}

bool AXYZWorker::IsWorkerInDistanceToPlace(const FIntVector2& CurrentGridPosition, const FIntVector2& PlacementCenterGridPosition, const FIntVector2& PlacementGridSize)
{
    int32 HalfSizeX = PlacementGridSize.X / 2;
    int32 HalfSizeY = PlacementGridSize.Y / 2;
    int32 MinX = PlacementCenterGridPosition.X - HalfSizeX;
    int32 MaxX = PlacementCenterGridPosition.X + HalfSizeX;
    int32 MinY = PlacementCenterGridPosition.Y - HalfSizeY;
    int32 MaxY = PlacementCenterGridPosition.Y + HalfSizeY;

    if(PlacementGridSize.X % 2 == 0) 
    {
        MaxX -= 1;
    }
    if(PlacementGridSize.Y % 2 == 0) 
    {
        MaxY -= 1;
    }

    bool bIsAdjacentX = CurrentGridPosition.X == MinX - 1 || CurrentGridPosition.X == MaxX + 1;
    bool bIsAdjacentY = CurrentGridPosition.Y == MinY - 1 || CurrentGridPosition.Y == MaxY + 1;

    return ((bIsAdjacentX && (CurrentGridPosition.Y >= MinY && CurrentGridPosition.Y <= MaxY)) || 
           (bIsAdjacentY && (CurrentGridPosition.X >= MinX && CurrentGridPosition.X <= MaxX)));
}

void AXYZWorker::ProcessFlyingWorker(float DeltaTime)
{
    if (State == EXYZUnitState::GATHERING) {
        if (!TargetActor) {
            FindClosestResource();
        }
        if (TargetActor) {
            FlyingGather(DeltaTime);
        }
        else {
            GetXYZAIController()->XYZStopMovement();
        }
    }
    else if (State == EXYZUnitState::RETURNING) {
        if (ClosestBase) {
            FlyingReturn(DeltaTime);
        }else
        {
            FindClosestBase();
        }
        if(!ClosestBase) {
            GetXYZAIController()->XYZStopMovement();
        }
    }
    else if (State == EXYZUnitState::MINING)
    {
        AXYZResourceActor* Resource = Cast<AXYZResourceActor>(TargetActor);
        if(!Resource || !Resource->Workers.Contains(this))
        {
            SetState(EXYZUnitState::GATHERING);
        }
        else
        {
            if(HeldResource != EXYZResourceType::NONE)
            {
                StartReturningResource();
            }
            else if(TimeToGather >= GatherRate)
            {
                TargetActor->Health = FMath::Clamp(TargetActor->Health - AttackDamage, 0.0f, TargetActor->MaxHealth);
                TimeToGather = 0;
                StartReturningResource();
            }
            else
            {
                if(Resource->Workers[this])
                {
                    TimeToGather += DeltaTime;
                }
                else if(Resource->Workers.Num() < Resource->RESOURCE_CAPACITY)
                {
                    Resource->Workers[this] = true;
                }
                else
                {
                    Resource->RemoveWorker(this);
                    TargetActor = nullptr;
                    SetState(EXYZUnitState::GATHERING);
                }
            }
        }
    }
}