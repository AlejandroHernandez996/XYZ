#include "XYZAttackAction.h"
#include "XYZActor.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZAttackAction::ProcessAction(float DeltaTime)
{
    Super::ProcessAction(DeltaTime);
    FVector ActorLocation = Actor->GetActorLocation();
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    if (TargetActor) {
        if (Actor == TargetActor) {
            CancelAction();
            return;
        }
        if (TargetActor->Health <= 0.0f) {
            if (bIsAttackMove) {
                TargetActor = nullptr;
            }
            else {
                CompleteAction();
            }
        }
        else {
            FVector TargetActorLocation = TargetActor->GetActorLocation();

            FVector Direction = TargetActorLocation - ActorLocation;
            Direction.Z = 0;
            Direction.Normalize();

            FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
            float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

            if (DistanceToTarget <= Actor->AttackRange)
            {
                Actor->GetController<AXYZAIController>()->StopMovement();
                AIController->bIsMoving = false;
                AIController->bHasCompletedMove = false;
                Actor->Attack(TargetActor);
            }
            else {
                Actor->GetController<AXYZAIController>()->MoveToActor(TargetActor, 50.0f, true, true, false, false);
            }
        }
    }
    else {
        TargetActor = Actor->FindClosestActor(bIgnoreAllies);

        if (!TargetActor) {
            if (!Actor->GetController<AXYZAIController>()->bIsMoving)  // Replace with your actual distance tolerance if necessary
            {
                AIController->MoveToLocation(TargetLocation, 50.0f, true, true, false, false);
            }
            else if (AIController->bHasCompletedMove)
            {
                CompleteAction();
                AIController->bIsMoving = false;
                AIController->bHasCompletedMove = false;
            }
        }
    } 
}

void UXYZAttackAction::CancelAction() {
    Super::CancelAction();
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    if (!AIController) return;
    AIController->bIsMoving = false;
    AIController->bHasCompletedMove = false;
}
void UXYZAttackAction::CompleteAction() {
    Super::CompleteAction();
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    if (!AIController) return;
    AIController->bIsMoving = false;
    AIController->bHasCompletedMove = false;
}