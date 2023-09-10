#include "XYZMoveAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZMoveAction::ProcessAction(float DeltaTime)
{
    Super::ProcessAction(DeltaTime);

    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    if (!Actor->GetController<AXYZAIController>()->bIsMoving)  // Replace with your actual distance tolerance if necessary
    {
        FVector Velocity = Actor->GetVelocity();
        AIController->MoveToLocation(TargetLocation);
        if (Velocity.Size() > Actor->GetVelocity().Size()) {
            FVector NewVelocity = Actor->GetVelocity();
            NewVelocity.Normalize();
            Actor->GetCharacterMovement()->Velocity = NewVelocity * Velocity.Size();
        }
        AIController->bIsMoving = true;
    }
    else if(AIController->bHasCompletedMove)
    {
        CompleteAction();
        AIController->bIsMoving = false;
        AIController->bHasCompletedMove = false;
    }
}

void UXYZMoveAction::CancelAction() {
    Super::CancelAction();
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    AIController->bIsMoving = false;
    AIController->bHasCompletedMove = false;
}
void UXYZMoveAction::CompleteAction() {
    Super::CompleteAction();
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    AIController->bIsMoving = false;
    AIController->bHasCompletedMove = false;
}