// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZActor.h"
#include "XYZAction.h"
#include "XYZGameState.h"
#include "XYZDecalType.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "XYZAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "XYZActionFactory.h"
#include "XYZResourceActor.h"
#include "XYZWorker.h"
#include "XYZBuilding.h"

// Sets default values
AXYZActor::AXYZActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
    bReplicates = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AXYZAIController::StaticClass();
    Health = 100.0f;
    MaxHealth = 100.0f;
}

void AXYZActor::BeginPlay()
{
    Super::BeginPlay();

    TArray<UActorComponent*> DecalComponents = GetComponentsByClass(UDecalComponent::StaticClass());
    if (DecalComponents.Num() == 1) {
        SelectionDecal = Cast<UDecalComponent>(DecalComponents[0]);
    }
    InitialCapsuleRadius = GetCapsuleComponent()->GetUnscaledCapsuleRadius();
}

void AXYZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (GetLocalRole() == ROLE_Authority) {
        if (Health == 0.0f)
        {
            if (this) {
                GetWorld()->GetFirstPlayerController<AXYZPlayerController>()->XYZActorDestroyed(UActorId);
                Destroy();
            }
        }
        if (State == EXYZUnitState::MOVING || State == EXYZUnitState::ATTACK_MOVING || State == EXYZUnitState::FOLLOWING) {
            ScanXYZActorsAhead();
        }
        if (State == EXYZUnitState::ATTACK_MOVING || State == EXYZUnitState::IDLE || State == EXYZUnitState::ATTACKING || State == EXYZUnitState::HOLD) {
            if (!TargetActor || TargetActor->Health <= 0.0f) {
                TargetActor = FindClosestActor(true);
            }
            if (TargetActor) {
                AttackMoveTarget();
            }
            if (!TargetActor && State == EXYZUnitState::ATTACKING) {
                SetState(EXYZUnitState::IDLE);
            }
        }
        if (State == EXYZUnitState::FOLLOWING) {
            if (!TargetActor || TargetActor->Health <= 0.0f) {
                GetXYZAIController()->StopMovement();
            }
            else {
                GetXYZAIController()->RecalculateMove();
            }
        }
        
    }
}

void AXYZActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AXYZActor, Health);
    DOREPLIFETIME(AXYZActor, MaxHealth);
    DOREPLIFETIME(AXYZActor, MoveSpeed);
    DOREPLIFETIME(AXYZActor, BaseArmor);
    DOREPLIFETIME(AXYZActor, AttackDamage);
    DOREPLIFETIME(AXYZActor, AttackRate);
    DOREPLIFETIME(AXYZActor, AttackRange);
    DOREPLIFETIME(AXYZActor, UActorId);
}

void AXYZActor::QueueAction(UXYZAction* Action) {
}

void AXYZActor::ShowDecal(bool bShowDecal, EXYZDecalType DecalType) {

    if (!SelectionDecal) return;
    if (!bShowDecal) {
        SelectionDecal->SetMaterial(0, DecalMaterials[EXYZDecalType::NEUTRAL]);
    }
    else {
        SelectionDecal->SetMaterial(0, DecalMaterials[DecalType]);
    }
}

void AXYZActor::Attack() {
    if (GetLocalRole() != ROLE_Authority) {
        return;
    }
    if (TargetActor && !bIsAttackOnCooldown) {
        bIsAttackOnCooldown = true;
        GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this]() {
            bIsAttackOnCooldown = false;
            }, AttackRate, false);
        TargetActor->Health = FMath::Clamp(TargetActor->Health - AttackDamage, 0.0f, TargetActor->MaxHealth);
        FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
        Direction.Z = 0; 
        Direction.Normalize();

        FRotator TargetRotation = Direction.Rotation();
        SetActorRotation(TargetRotation);
        UE_LOG(LogTemp, Warning, TEXT("Attacking for %d enemy health %d"), AttackDamage, TargetActor->Health);
    }
}

AXYZActor* AXYZActor::FindClosestActor(bool bIgnoreFriendlyActors) {

    AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();

    AXYZActor* ClosestActor = nullptr;
    float ClosestDistanceSqr = FLT_MAX;
    for (AXYZActor* OtherActor : GameState->GetAllActors())
    {
        bool bTargetIsFriendlyAndShouldIgnore = OtherActor->TeamId == TeamId && bIgnoreFriendlyActors;
        if (!OtherActor || OtherActor == this || bTargetIsFriendlyAndShouldIgnore || OtherActor->Health <= 0.0f || OtherActor->IsA(AXYZResourceActor::StaticClass())) {
            continue;
        }

        float DistanceSqr = FVector::DistSquaredXY(this->GetActorLocation(), OtherActor->GetActorLocation());

        if (DistanceSqr < ClosestDistanceSqr && DistanceSqr <= FMath::Square(VisionRange))
        {
            ClosestDistanceSqr = DistanceSqr;
            ClosestActor = OtherActor;
        }
    }

    return ClosestActor;
}

AXYZAIController* AXYZActor::GetXYZAIController() {
    if (!XYZAIController) {
        XYZAIController = GetController<AXYZAIController>();
    }
    return XYZAIController;
}

void AXYZActor::ScanXYZActorsAhead() {
    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    float Distance = 60.0f;

    FVector End = ((ForwardVector * Distance) + Start);

    FVector LeftVector = ForwardVector.RotateAngleAxis(-45, FVector(0, 0, 1));
    FVector EndLeft = ((LeftVector * Distance) + Start);

    FVector RightVector = ForwardVector.RotateAngleAxis(45, FVector(0, 0, 1));
    FVector EndRight = ((RightVector * Distance) + Start);

    FVector Left22Vector = ForwardVector.RotateAngleAxis(-22, FVector(0, 0, 1));
    FVector End22Left = ((LeftVector * Distance) + Start);

    FVector Right22Vector = ForwardVector.RotateAngleAxis(22, FVector(0, 0, 1));
    FVector End22Right = ((RightVector * Distance) + Start);

    TSet<AXYZActor*> ActorsFound;
    ActorsFound.Add(ScanAndPush(Start, EndLeft, ActorsFound));
    ActorsFound.Add(ScanAndPush(Start, End22Left, ActorsFound));
    ActorsFound.Add(ScanAndPush(Start, EndRight, ActorsFound));
    ActorsFound.Add(ScanAndPush(Start, End22Right, ActorsFound));
    ActorsFound.Add(ScanAndPush(Start, End, ActorsFound));
}

AXYZActor* AXYZActor::ScanAndPush(FVector Start, FVector End, TSet<AXYZActor*> ActorsFound) {
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams);

    if (bHit && HitResult.GetActor() && 
        HitResult.GetActor()->IsA(AXYZActor::StaticClass()) && 
        !HitResult.GetActor()->IsA(AXYZBuilding::StaticClass()) && 
        !HitResult.GetActor()->IsA(AXYZWorker::StaticClass()))
    {
        AXYZActor* OtherXYZActor = Cast<AXYZActor>(HitResult.GetActor());
       
        if (!OtherXYZActor || OtherXYZActor == TargetActor) return nullptr;
        if (OtherXYZActor->State == EXYZUnitState::IDLE && !ActorsFound.Contains(OtherXYZActor) && OtherXYZActor->TeamId == TeamId)
        {
            FVector Direction = End - Start;
            Direction.Normalize();
            FVector PushLocation = (Direction * 100.0f) + OtherXYZActor->GetActorLocation();
            if (Direction == GetActorForwardVector()) {
                PushLocation = (OtherXYZActor->GetActorRightVector() * 100.0f) + OtherXYZActor->GetActorLocation();
            }
            OtherXYZActor->GetXYZAIController()->XYZMoveToLocation(PushLocation);
            return OtherXYZActor;
        }
        if (OtherXYZActor && OtherXYZActor->State == EXYZUnitState::ATTACKING && !ActorsFound.Contains(OtherXYZActor)) {
            GetXYZAIController()->RecalculateMove();
            return OtherXYZActor;
        }
    }

    return nullptr;
}

void AXYZActor::AttackMoveTarget() {
    AXYZAIController* ActorController = GetXYZAIController();
    FVector ActorLocation = GetActorLocation();
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    if (TargetActor != this && TargetActor->Health > 0.0f) {
        
        FVector TargetActorLocation = TargetActor->GetActorLocation();
        
        FVector Direction = TargetActorLocation - ActorLocation;
        Direction.Z = 0;
        Direction.Normalize();
        
        FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
        float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);
        
        if (DistanceToTarget <= AttackRange)
        {
            Attack();
            if (State != EXYZUnitState::HOLD) {
                SetState(EXYZUnitState::ATTACKING);
                ActorController->XYZStopMovement();
            }
        }
        else if(State != EXYZUnitState::HOLD){
            ActorController->XYZAttackMoveToLocation(TargetActor->GetActorLocation());
            TargetActor = nullptr;
        }
    }
    else {
        TargetActor = nullptr;
    }
    
}

void AXYZActor::SetState(EXYZUnitState UnitState) {
    PreviousState = State;
    State = UnitState;
    switch (State) {
    case EXYZUnitState::GATHERING:
        break;
    case EXYZUnitState::RETURNING:
        break;
    case EXYZUnitState::IDLE:
        TargetActor = nullptr;
        break;
    case EXYZUnitState::MOVING:
        TargetActor = nullptr;
        break;
    case EXYZUnitState::ATTACK_MOVING:
        break;
    case EXYZUnitState::ATTACKING:
        break;
    }
}