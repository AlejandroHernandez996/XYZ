#include "XYZEvadeAction.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZEvadeAction::ProcessAction(float DeltaTime)
{
    Super::ProcessAction(DeltaTime);
    Actor->State = EXYZUnitState::IDLE;

    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    if (!Actor->GetController<AXYZAIController>()->bIsMoving)  // Replace with your actual distance tolerance if necessary
    {
        AIController->MoveToLocation(TargetLocation);
        AIController->bIsMoving = true;
    }
    else if (AIController->bHasCompletedMove)
    {
        CompleteAction();
        AIController->bIsMoving = false;
        AIController->bHasCompletedMove = false;
    }
}

void UXYZEvadeAction::CancelAction() {
    Super::CancelAction();
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    AIController->bIsMoving = false;
    AIController->bHasCompletedMove = false;
}
void UXYZEvadeAction::CompleteAction() {
    Super::CompleteAction();
    AXYZAIController* AIController = Actor->GetController<AXYZAIController>();
    AIController->bIsMoving = false;
    AIController->bHasCompletedMove = false;
}