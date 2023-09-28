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
        GetCharacterMovement()->bUseRVOAvoidance = false;
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
        GetCharacterMovement()->bUseRVOAvoidance = false;
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
        TimeToGather += DeltaTime;
    }
    else {
        GetCharacterMovement()->bUseRVOAvoidance = true;
    }
}

void AXYZWorker::Gather() {
    AXYZAIController* ActorController = GetXYZAIController();
    FVector ActorLocation = GetActorLocation() + GetActorForwardVector() * CurrentCapsuleRadius;
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    if (TargetActor && TargetActor->IsA(AXYZResourceActor::StaticClass()) && TargetActor->Health > 0.0f) {

        UCapsuleComponent* CapsuleComp = TargetActor->GetCapsuleComponent();
        FVector ClosestPoint;
        CapsuleComp->GetClosestPointOnCollision(ActorLocation, ClosestPoint);

        FVector2D TargetLocation2D = FVector2D(ClosestPoint.X, ClosestPoint.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

        if (DistanceToTarget <= CurrentCapsuleRadius * 3.0f && !bIsGatheringResource)
        {
            bIsGatheringResource = true;
            GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AXYZWorker::StartReturningResource, GatherRate, false);
            TargetActor->Health = FMath::Clamp(TargetActor->Health - AttackDamage, 0.0f, TargetActor->MaxHealth);
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
    if (State == EXYZUnitState::GATHERING) {
        if(TargetActor && TargetActor->IsA(AXYZResourceActor::StaticClass()))
        {
            HeldResource = Cast<AXYZResourceActor>(TargetActor)->ResourceType;
            TargetActor->Health -= 5;
            FindClosestBase();
            if (ClosestBase) {
                GetXYZAIController()->XYZReturnResource(ClosestBase);
            }
        }else
        {
            SetState(EXYZUnitState::IDLE);
        }
       
    }
    bIsGatheringResource = false;
}
void AXYZWorker::Return() {
    AXYZAIController* ActorController = GetXYZAIController();
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
            if (!TargetActor || !TargetActor->IsA(AXYZResourceActor::StaticClass())) {
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

    AXYZResourceActor* ClosestResource = nullptr;
    float ClosestDistance = FLT_MAX;

    for (AActor* Resource : FoundResources)
    {
        float Distance = FVector::Dist(Resource->GetActorLocation(), GetActorLocation());
        if (Distance < ClosestDistance && Resource->IsA(AXYZResourceActor::StaticClass()))
        {
            ClosestDistance = Distance;
            ClosestResource = Cast<AXYZResourceActor>(Resource);
        }
    }

    TargetActor = ClosestResource;
}

void AXYZWorker::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AXYZWorker, HeldResource);
}