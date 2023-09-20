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
        if (GetPawn<AXYZActor>()->State != EXYZUnitState::ATTACKING && GetPawn<AXYZActor>()->State != EXYZUnitState::GATHERING && GetPawn<AXYZActor>()->State != EXYZUnitState::RETURNING) {
            GetPawn<AXYZActor>()->SetState(EXYZUnitState::IDLE);
            GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(GetPawn<AXYZActor>()->InitialCapsuleRadius);
            GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
            GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
        }
        bIsMoving = false;
    }
}

void AXYZAIController::XYZMoveToActor(AXYZActor* Actor, float AcceptanceRadius) {
    if (!Actor || GetPawn<AXYZActor>() == Actor) {
        XYZStopMovement();
        return;
    }
    MoveToActor(Actor, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::MOVING);
    CurrentTargetLocation = Actor->GetActorLocation();
    bIsMoving = true;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
}

void AXYZAIController::XYZMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>()) return;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::MOVING);
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;

    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
}

void AXYZAIController::XYZAttackMoveToLocation(FVector TargetLocation, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>()) return;
    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, false);
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::ATTACK_MOVING);
    CurrentTargetLocation = TargetLocation;
    bIsMoving = true;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
}

void AXYZAIController::XYZAttackMoveToTarget(AXYZActor* Actor, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>() || !Actor || GetPawn<AXYZActor>() == Actor) {
        XYZStopMovement();
        return;
    }
    MoveToActor(Actor, AcceptanceRadius, true, true, false, false);
    CurrentTargetLocation = Actor->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::ATTACK_MOVING);
    GetPawn<AXYZActor>()->TargetActor = Actor;
    bIsMoving = true;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
}

void AXYZAIController::XYZFollowTarget(AXYZActor* Actor, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>() || !Actor || GetPawn<AXYZActor>() == Actor) {
        XYZStopMovement();
        return;
    }
    MoveToActor(Actor, AcceptanceRadius, true, true, false, false);
    CurrentTargetLocation = Actor->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::FOLLOWING);
    GetPawn<AXYZActor>()->TargetActor = Actor;
    bIsMoving = true;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
}

void AXYZAIController::XYZGatherResource(AXYZResourceActor* Resource, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>() || !Resource || !GetPawn<AXYZActor>()->IsA(AXYZWorker::StaticClass())) {
        XYZStopMovement();
        return;
    }
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = false;
    // Assume TargetActor is the actor you are facing.
    UCapsuleComponent* CapsuleComp = Resource->GetCapsuleComponent();
    FVector MyLocation = GetPawn<AXYZActor>()->GetActorLocation();
    FVector TargetLocation = Resource->GetActorLocation();
    FVector ClosestPoint;
    CapsuleComp->GetClosestPointOnCollision(MyLocation, ClosestPoint);
    MoveToLocation(ClosestPoint, AcceptanceRadius, true, true, false, false);
    CurrentTargetLocation = Resource->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::GATHERING);
    GetPawn<AXYZActor>()->TargetActor = Resource;
    bIsMoving = true;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("MineralWalk");
}

void AXYZAIController::XYZReturnResource(AXYZBaseBuilding* Base, float AcceptanceRadius) {
    if (!GetPawn<AXYZActor>() || !Base || !GetPawn<AXYZActor>()->IsA(AXYZWorker::StaticClass())) {
        XYZStopMovement();
        return;
    }
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = false;
    UCapsuleComponent* CapsuleComp = Base->GetCapsuleComponent();
    FVector MyLocation = GetPawn<AXYZActor>()->GetActorLocation();
    FVector TargetLocation = Base->GetActorLocation();
    FVector ClosestPoint;
    CapsuleComp->GetClosestPointOnCollision(MyLocation, ClosestPoint);
    MoveToLocation(ClosestPoint, AcceptanceRadius, true, true, false, false);
    CurrentTargetLocation = Base->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::RETURNING);
    bIsMoving = true;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(35.0f);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("MineralWalk");
}

void AXYZAIController::XYZStopMovement() {
    if (!GetPawn<AXYZActor>()) return;
    StopMovement();
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
    CurrentTargetLocation = GetPawn<AXYZActor>()->GetActorLocation();
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
    bIsMoving = false;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(GetPawn<AXYZActor>()->InitialCapsuleRadius);

    if (GetPawn<AXYZActor>()->State != EXYZUnitState::ATTACKING && GetPawn<AXYZActor>()->State == EXYZUnitState::RETURNING && GetPawn<AXYZActor>()->State == EXYZUnitState::GATHERING) {
        GetPawn<AXYZActor>()->SetState(EXYZUnitState::IDLE);
    }
}

void AXYZAIController::XYZHold() {
    if (!GetPawn<AXYZActor>()) return;
    StopMovement();
    GetPawn<AXYZActor>()->GetCharacterMovement()->bUseRVOAvoidance = true;
    CurrentTargetLocation = GetPawn<AXYZActor>()->GetActorLocation();
    GetPawn<AXYZActor>()->SetState(EXYZUnitState::HOLD);
    bIsMoving = false;
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCapsuleRadius(GetPawn<AXYZActor>()->InitialCapsuleRadius);
    GetPawn<AXYZActor>()->GetCapsuleComponent()->SetCollisionProfileName("Pawn");
}
void AXYZAIController::RecalculateMove() {
    if (!GetPawn<AXYZActor>()) return;
    switch (GetPawn<AXYZActor>()->State) {
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
        XYZFollowTarget(GetPawn<AXYZActor>()->TargetActor);
        break;
    }
}