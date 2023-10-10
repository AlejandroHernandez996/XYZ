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
    if (FloatingMesh && !HasAuthority()) {
        float Time = GetWorld()->GetTimeSeconds();
        FVector NewLocation = FloatingMesh->GetRelativeLocation();

        NewLocation.Z += FMath::Sin(Time * FloatSpeed) * FloatAmplitude * DeltaTime;
        FloatingMesh->SetRelativeLocation(NewLocation);
    }
    
}

void AXYZWorker::Process(float DeltaTime)
{
    Super::Process(DeltaTime);
    if(State == EXYZUnitState::PLACING)
    {
        if(ActivePlacementAbility)
        {
            FVector WorkerCurrentLocation = GetActorLocation();
            FVector PlacingLocation = ActivePlacementAbility->BuildingLocation;

            FVector2D WorkerCurrentLocation2D(WorkerCurrentLocation.X, WorkerCurrentLocation.Y);
            FVector2D PlacingLocation2D(PlacingLocation.X, PlacingLocation.Y);

            float Distance2D = FVector2D::Distance(WorkerCurrentLocation2D, PlacingLocation2D);
            UE_LOG(LogTemp, Warning, TEXT("Distance2D: %f"), Distance2D);

            if(Distance2D <= GetCapsuleComponent()->GetScaledCapsuleRadius()*2.5f)
            {
                PlaceBuilding();
            }
            else if(XYZAIController)
            {
                FVector Start = PlacingLocation;
                Start.Z = 10000.0f;
                FVector End = PlacingLocation;
                End.Z = -10000.0f;
                FHitResult HitResult;

                FCollisionQueryParams CollisionParams;

                FCollisionObjectQueryParams ObjectQueryParams;
                ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

                bool bHit = GetWorld()->LineTraceSingleByObjectType(
                    HitResult,
                    Start,
                    End,
                    ObjectQueryParams,
                    CollisionParams
                );
                if (bHit)
                {
                    float HitZValue = HitResult.Location.Z;
                    XYZAIController->MoveToLocation(FVector(PlacingLocation.X, PlacingLocation.Y, HitZValue));
                }else
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
    else {
        GetCharacterMovement()->bUseRVOAvoidance = true;
    }
}

void AXYZWorker::Gather() {
    AXYZAIController* ActorController = GetXYZAIController();
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
                GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->GasByTeamId[TeamId] += 5;
            }
            HeldResource = EXYZResourceType::NONE;
            if(!TargetActor)
            {
                FindClosestResource();
            }
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
        if (ResourceActor && Distance <= 1000.0f)
        {
            if(ResourceActor->Workers.Num() < SmallestCapacity)
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
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        FVector SpawnLocation = ActivePlacementAbility->BuildingLocation;
    
        FVector Start = SpawnLocation + FVector(0, 0, 1000); 
        FVector End = SpawnLocation - FVector(0, 0, 10000);  

        FHitResult HitResult;

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic);

        if (bHit)
        {
            SpawnLocation.Z = HitResult.Location.Z;
        }

        AXYZActor* SpawnActor = GetWorld()->SpawnActor<AXYZActor>(ActivePlacementAbility->BuildingTemplate, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        SpawnActor->TeamId = TeamId;
        GetWorld()->GetAuthGameMode()->GetGameState<AXYZGameState>()->AddActorServer(SpawnActor);
        FVector OffsetLocation = SpawnActor->GetActorLocation();
        OffsetLocation.Z += SpawnActor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
        SpawnActor->SetActorLocation(OffsetLocation);
        ActivePlacementAbility = nullptr;
        AXYZBuilding* SpawnedBuilding = Cast<AXYZBuilding>(SpawnActor);
        if(Cast<AXYZBuilding>(SpawnActor))
        {
            SpawnedBuilding->BuildingState = EXYZBuildingState::PLACED;
            SpawnedBuilding->Health = 5.0f;
        }
        GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->AddToUpdateSet(SpawnActor);
        SetState(EXYZUnitState::BUILDING);
    }else
    {
        SetState(EXYZUnitState::IDLE);
    }
    
}
