#include "XYZMoveAction.h"
#include "XYZActor.h"

void UXYZMoveAction::ProcessAction(float DeltaTime)
{
    Super::ProcessAction(DeltaTime);

    FVector ActorLocation = Actor->GetActorLocation();

    // Calculate direction vector
    FVector Direction = TargetLocation - ActorLocation;
    Direction.Z = 0; // Assuming you only want to move in the XY plane
    Direction.Normalize();

    // Check if the actor is already close enough to the target location
    FVector2D ActorLocation2D = FVector2D(ActorLocation.X, ActorLocation.Y);
    FVector2D TargetLocation2D = FVector2D(TargetLocation.X, TargetLocation.Y);
    float DistanceToTarget = FVector2D::Distance(ActorLocation2D, TargetLocation2D);

    if (DistanceToTarget > TargetLocationThreshold)  // Replace with your actual distance tolerance if necessary
    {
        // Calculate new location
        FVector NewLocation = ActorLocation + (Direction * Actor->MoveSpeed * DeltaTime);

        // Set the new location
        Actor->SetActorLocation(NewLocation);
    }
    else
    {
        CompleteAction();
        UE_LOG(LogTemp, Warning, TEXT("Action completed"));
    }
}