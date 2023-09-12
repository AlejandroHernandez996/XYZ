#include "XYZAttackAction.h"
#include "XYZActor.h"
#include "XYZActor.h"
#include "XYZAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZAttackAction::ProcessAction(float DeltaTime)
{
    Super::ProcessAction(DeltaTime);
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