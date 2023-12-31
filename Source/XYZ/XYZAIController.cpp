// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZAIController.h"

#include "Components/CapsuleComponent.h"
#include "XYZActor.h"
#include "XYZResourceActor.h"
#include "XYZWorker.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XYZBaseBuilding.h"
#include "XYZGameMode.h"
#include "XYZMapManager.h"

void AXYZAIController::BeginPlay()
{
    Super::BeginPlay();

    if (GetPathFollowingComponent())
    {
        GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AXYZAIController::OnMoveCompleted);
    }
}

void AXYZAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.Code == EPathFollowingResult::Success)
    {
        if (GetXYZActor()->State != EXYZUnitState::ATTACKING &&
            GetXYZActor()->State != EXYZUnitState::GATHERING &&
            GetXYZActor()->State != EXYZUnitState::RETURNING &&
            GetXYZActor()->State != EXYZUnitState::FOLLOWING &&
            GetXYZActor()->State != EXYZUnitState::PLACING) {
            GetXYZActor()->SetState(EXYZUnitState::IDLE);
            GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius;
            GetXYZActor()->CollisionName = "Unit";
            GetXYZActor()->PushedBy = nullptr;
            GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
        }
        GetXYZActor()->bIsInBoidMovement = false;
        bIsMoving = false;
    }
}

void AXYZAIController::XYZMoveToActor(AXYZActor* Actor, float AcceptanceRadius) {
    if (!Actor || GetXYZActor() == Actor) {
        XYZStopMovement();
        return;
    }
    AXYZBuilding* Building = Cast<AXYZBuilding>(GetXYZActor());
    if (Building) {
        Building->RallyTarget = Actor;
        return;
    }
    if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && Actor->IsA(AXYZResourceActor::StaticClass())) {
        XYZGatherResource(Cast<AXYZResourceActor>(Actor));
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    GetXYZActor()->SetState(EXYZUnitState::MOVING);
    CurrentTargetLocation = Actor->GetActorLocation();
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius* 0.75f;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 2.0f;
    MoveToActor(Actor, AcceptanceRadius, true, true, false);
}

void AXYZAIController::XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetXYZActor()) return;
    AXYZBuilding* Building = Cast<AXYZBuilding>(GetXYZActor());
    if (Building) {
        Building->RallyPoint = TargetLocation;
        if(Building->RallyTarget)
        {
            Building->RallyTarget = nullptr;
        }
        return;
    }
    GetXYZActor()->SetState(EXYZUnitState::MOVING);
    GetXYZActor()->TargetLocation = TargetLocation;
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;
    GetXYZActor()->bIsInBoidMovement = false;

    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->bHasAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 2.0f;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
}

void AXYZAIController::XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetXYZActor()) return;
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    GetXYZActor()->TimeSinceLastUpdate = 0.0f;
    GetXYZActor()->TimeSinceScanForTarget = 0.0f;
    GetXYZActor()->SetState(EXYZUnitState::ATTACK_MOVING);
    GetXYZActor()->TargetLocation = TargetLocation;
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 3.0f;
    GetXYZActor()->TimeSinceScanForTarget = 0.0f;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
}

void AXYZAIController::XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius) {
    if(GetXYZActor()->bIsPassive)
    {
       XYZFollowTarget(Actor);
        return;
    }
    if (!GetXYZActor() || !Actor || GetXYZActor() == Actor) {
        XYZStopMovement();
        return;
    }
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        Cast<AXYZBuilding>(GetXYZActor())->RallyTarget = Actor;
        Cast<AXYZBuilding>(GetXYZActor())->TargetActor = Actor;
        return;
    }
    if (Actor->IsA(AXYZResourceActor::StaticClass())) {
        XYZMoveToActor(Actor);
        return;
    }
    CurrentTargetLocation = Actor->GetActorLocation();
    GetXYZActor()->TargetLocation = Actor->GetTargetLocation();
    if(Actor->bIsFlying)
    {
        GetXYZActor()->TargetLocation = GetXYZActor()->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->GridCoordToWorldCoord(Actor->GridCoord);
    }
    GetXYZActor()->SetState(EXYZUnitState::ATTACKING);
    GetXYZActor()->TargetActor = Actor;
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 3.0f;
    GetXYZActor()->bIsInBoidMovement = false;

    if(Actor->bIsFlying)
    {
        FVector FlyingActorLocation = GetXYZActor()->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MapManager->GridCoordToWorldCoord(Actor->GridCoord);
        MoveToLocation(FlyingActorLocation, AcceptanceRadius, true, true, false);
    }else
    {
        MoveToActor(Actor, AcceptanceRadius, true, true, false);
    }
}

void AXYZAIController::XYZFollowTarget(AXYZActor* Actor, float AcceptanceRadius) {
    if (!GetXYZActor() || !Actor || GetXYZActor() == Actor) {
        XYZStopMovement();
        return;
    }
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        Cast<AXYZBuilding>(GetXYZActor())->RallyTarget = Actor;
        return;
    }
    if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && Cast<AXYZWorker>(GetXYZActor())->HeldResource != EXYZResourceType::NONE && Actor->IsA(AXYZBaseBuilding::StaticClass())) {
        Cast<AXYZWorker>(GetXYZActor())->StartReturningResource();
        Cast<AXYZWorker>(GetXYZActor())->FindClosestBase();
        if (Cast<AXYZWorker>(GetXYZActor())->ClosestBase) {
            XYZReturnResource(Cast<AXYZWorker>(GetXYZActor())->ClosestBase);
        }
        return;
    }
    if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && Actor->IsA(AXYZResourceActor::StaticClass())) {
        XYZGatherResource(Cast<AXYZResourceActor>(Actor));
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    CurrentTargetLocation = Actor->GetActorLocation();
    GetXYZActor()->SetState(EXYZUnitState::FOLLOWING);
    GetXYZActor()->TargetActor = Actor;
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 2.0f;
    MoveToActor(Actor,GetXYZActor()->GetCapsuleComponent()->GetScaledCapsuleRadius()*2.0f , true, true, false);
}

void AXYZAIController::XYZGatherResource(AXYZResourceActor* Resource, float AcceptanceRadius) {
    if (!GetXYZActor() || !Resource || !GetXYZActor()->IsA(AXYZWorker::StaticClass())) {
        XYZStopMovement();
        return;
    }
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    GetXYZActor()->bHasAvoidance = false;
    GetXYZActor()->CollisionName = "MineralWalk";
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->SetState(EXYZUnitState::GATHERING);
    Cast<AXYZWorker>(GetXYZActor())->ResourceToGather = Resource->ResourceType;
    GetXYZActor()->TargetActor = Resource;

    UCapsuleComponent* CapsuleComp = Resource->GetCapsuleComponent();
    FVector MyLocation = GetXYZActor()->GetActorLocation();
    FVector TargetLocation = Resource->GetActorLocation();
    FVector ClosestPoint;
    CapsuleComp->GetClosestPointOnCollision(MyLocation, ClosestPoint);

    MoveToLocation(ClosestPoint, AcceptanceRadius, true, true, false, false);

    bIsMoving = true;
    CurrentTargetLocation = ClosestPoint;
}

void AXYZAIController::XYZReturnResource(AXYZBaseBuilding* Base, float AcceptanceRadius) {
    if (!GetXYZActor() || !Base || !GetXYZActor()->IsA(AXYZWorker::StaticClass())) {
        XYZStopMovement();
        return;
    }
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    GetXYZActor()->bHasAvoidance = false;
    GetXYZActor()->SetState(EXYZUnitState::RETURNING);
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "MineralWalk";
    UCapsuleComponent* CapsuleComp = Base->GetCapsuleComponent();
    FVector MyLocation = GetXYZActor()->GetActorLocation();
    FVector TargetLocation = Base->GetActorLocation();
    FVector ClosestPoint;
    CapsuleComp->GetClosestPointOnCollision(MyLocation, ClosestPoint);

    MoveToLocation(ClosestPoint, AcceptanceRadius, true, true, false, false);

    bIsMoving = true;
    CurrentTargetLocation = ClosestPoint;
}

void AXYZAIController::XYZStopMovement() {
    if (!GetXYZActor()) return;
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    StopMovement();
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 1.0f;
    bIsMoving = false;
    GetXYZActor()->PushedBy = nullptr;
    CurrentTargetLocation = GetXYZActor()->GetActorLocation();

    if (GetXYZActor()->State != EXYZUnitState::ATTACKING && GetXYZActor()->State != EXYZUnitState::HOLD) {
        GetXYZActor()->SetState(EXYZUnitState::IDLE);
    }
}

void AXYZAIController::XYZHold() {
    if (!GetXYZActor()) return;
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->bIsInBoidMovement = false;
    StopMovement();
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->SetState(EXYZUnitState::HOLD);
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius;
    GetXYZActor()->CollisionName = "Unit";
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 1.0f;
    bIsMoving = false;
    GetXYZActor()->TargetActor = nullptr;
    CurrentTargetLocation = GetXYZActor()->GetActorLocation();

}
void AXYZAIController::RecalculateMove() {
    if (!GetXYZActor()) return;
    GetXYZActor()->bIsInBoidMovement = false;
    switch (GetXYZActor()->State) {
    case EXYZUnitState::IDLE :
        XYZStopMovement();
        break;
    case EXYZUnitState::MOVING:
        XYZMoveToLocation(CurrentTargetLocation);
        break;
    case EXYZUnitState::ATTACK_MOVING:
        XYZAttackMoveToLocation(CurrentTargetLocation);
        break;
    case EXYZUnitState::ATTACKING:
        XYZAttackMoveToTarget(GetXYZActor()->TargetActor);
        break;
    case EXYZUnitState::FOLLOWING:
        XYZFollowTarget(GetXYZActor()->TargetActor);
        break;
    }
}

AXYZActor* AXYZAIController::GetXYZActor() {
    return GetPawn<AXYZActor>();
}