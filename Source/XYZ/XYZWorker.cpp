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
#include "Net/UnrealNetwork.h"

void AXYZWorker::BeginPlay() {
    Super::BeginPlay();
    State = EXYZUnitState::GATHERING;
}

void AXYZWorker::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
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
        FindClosestBase();
        if (ClosestBase) {
            Return();
        }
        else {
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

        if (DistanceToTarget <= CurrentCapsuleRadius * 3.0f)
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
    if(State == EXYZUnitState::MINING && NewState != EXYZUnitState::RETURNING && EXYZUnitState::GATHERING != NewState)
    {
        if(AXYZResourceActor* Resource = Cast<AXYZResourceActor>(TargetActor))
        {
            Resource->RemoveWorker(this);
        }
        TargetActor = nullptr;
    }
    else if(NewState == EXYZUnitState::DEAD ||
        NewState == EXYZUnitState::MOVING ||
        NewState == EXYZUnitState::HOLD ||
        NewState == EXYZUnitState::FOLLOWING ||
        NewState == EXYZUnitState::IDLE ||
        NewState == EXYZUnitState::ATTACK_MOVING ||
        NewState == EXYZUnitState::ATTACKING)
    {
        if(AXYZResourceActor* Resource = Cast<AXYZResourceActor>(TargetActor))
        {
            Resource->RemoveWorker(this);
        }
        TargetActor = nullptr;
    }
    Super::SetState(NewState);
}