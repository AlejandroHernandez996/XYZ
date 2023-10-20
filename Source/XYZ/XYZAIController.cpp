// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZAIController.h"

#include "Components/CapsuleComponent.h"
#include "XYZActor.h"
#include "XYZResourceActor.h"
#include "XYZWorker.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XYZBaseBuilding.h"

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
            GetXYZActor()->CollisionName = "Pawn";
            GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
        }
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
    GetXYZActor()->SetState(EXYZUnitState::MOVING);
    CurrentTargetLocation = Actor->GetActorLocation();
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius* 0.75f;
    GetXYZActor()->CollisionName = "Pawn";
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
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;

    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Pawn";
    GetXYZActor()->bHasAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 2.0f;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
}

void AXYZAIController::XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetXYZActor()) return;
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->SetState(EXYZUnitState::ATTACK_MOVING);
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Pawn";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 3.0f;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
}

void AXYZAIController::XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius) {
    if (!GetXYZActor() || !Actor || GetXYZActor() == Actor) {
        XYZStopMovement();
        return;
    }
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        Cast<AXYZBuilding>(GetXYZActor())->RallyTarget = Actor;
        return;
    }
    if (Actor->IsA(AXYZResourceActor::StaticClass())) {
        XYZMoveToActor(Actor);
        return;
    }
    CurrentTargetLocation = Actor->GetActorLocation();
    GetXYZActor()->SetState(EXYZUnitState::ATTACKING);
    GetXYZActor()->TargetActor = Actor;
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Pawn";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 3.0f;
    MoveToActor(Actor, AcceptanceRadius, true, true, false);
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
    if (GetXYZActor()->IsA(AXYZWorker::StaticClass()) && Cast<AXYZWorker>(GetXYZActor())->HeldResource == EXYZResourceType::MINERAL && Actor->IsA(AXYZBaseBuilding::StaticClass())) {
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

    CurrentTargetLocation = Actor->GetActorLocation();
    GetXYZActor()->SetState(EXYZUnitState::FOLLOWING);
    GetXYZActor()->TargetActor = Actor;
    bIsMoving = true;
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->CollisionName = "Pawn";
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 2.0f;
    MoveToActor(Actor, 30.0f, true, true, false);
}

void AXYZAIController::XYZGatherResource(AXYZResourceActor* Resource, float AcceptanceRadius) {
    if (!GetXYZActor() || !Resource || !GetXYZActor()->IsA(AXYZWorker::StaticClass())) {
        XYZStopMovement();
        return;
    }
    if (GetXYZActor()->IsA(AXYZBuilding::StaticClass())) {
        return;
    }
    GetXYZActor()->bHasAvoidance = false;
    GetXYZActor()->CollisionName = "MineralWalk";
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius * 0.75f;
    GetXYZActor()->SetState(EXYZUnitState::GATHERING);
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
    StopMovement();
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->CollisionName = "Pawn";
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius;
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 1.0f;
    bIsMoving = false;
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
    StopMovement();
    GetXYZActor()->GetCharacterMovement()->bUseRVOAvoidance = true;
    GetXYZActor()->SetState(EXYZUnitState::HOLD);
    GetXYZActor()->CurrentCapsuleRadius = GetXYZActor()->InitialCapsuleRadius;
    GetXYZActor()->CollisionName = "Pawn";
    GetXYZActor()->CurrentAvoidanceWeight = GetXYZActor()->DefaultAvoidanceWeight * 1.0f;
    bIsMoving = false;
    GetXYZActor()->TargetActor = nullptr;
    CurrentTargetLocation = GetXYZActor()->GetActorLocation();

}
void AXYZAIController::RecalculateMove() {
    if (!GetXYZActor()) return;
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
    case EXYZUnitState::FOLLOWING:
        XYZFollowTarget(GetXYZActor()->TargetActor);
        break;
    }
}

AXYZActor* AXYZAIController::GetXYZActor() {
    return GetPawn<AXYZActor>();
}