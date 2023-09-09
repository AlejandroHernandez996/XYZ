#include "XYZAttackAction.h"
#include "XYZActor.h"

void UXYZAttackAction::ProcessAction(float DeltaTime)
{
    Super::ProcessAction(DeltaTime);

    if (ActionState != EXYZActionState::IN_PROGRESS)
    {
        return;
    }
    if (!Actor)
    {
        CancelAction();
        return;
    }
    FVector ActorLocation = Actor->GetActorLocation();
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);

    if (!TargetActor) {
        TargetActor = Actor->FindClosestActor();

        if (!TargetActor) {
            FVector Direction = TargetLocation - ActorLocation;
            Direction.Z = 0; 
            Direction.Normalize();

            FVector2D TargetLocation2D = FVector2D(TargetLocation.X, TargetLocation.Y);
            float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

            if (DistanceToTarget > TargetLocationThreshold) 
            {
                FVector NewLocation = ActorLocation + (Direction * Actor->MoveSpeed * DeltaTime);
                Actor->SetActorLocation(NewLocation);
            }
            else
            {
                CompleteAction();
            }
            return;
        }
    } 

    if (TargetActor->Health <= 0.0f) {
        CompleteAction();
        return;
    }

    FVector TargetActorLocation = TargetActor->GetActorLocation();

    FVector Direction = TargetActorLocation - ActorLocation;
    Direction.Z = 0; 
    Direction.Normalize();

    FVector2D TargetLocation2D = FVector2D(TargetActorLocation.X, TargetActorLocation.Y);
    float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

    if (DistanceToTarget > Actor->AttackRange)  
    {
        FVector NewLocation = ActorLocation + (Direction * Actor->MoveSpeed * DeltaTime);
        Actor->SetActorLocation(NewLocation);
    }
    else
    {
        Actor->Attack(TargetActor);
    }
}