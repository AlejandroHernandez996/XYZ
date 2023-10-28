#include "XYZMoveBatcher.h"
#include "XYZActor.h"
#include "XYZAIController.h"
void UXYZMoveBatcher::Process(float DeltaTime)
{
	TSet<TSharedPtr<FXYZMove>> MovesProcessed;

	int ProcessIndex = 0;
	for(TSharedPtr<FXYZMove> XYZMove : MovesToProcess)
	{
		if(ProcessIndex >= BatchSize) break;

		if(!XYZMove || !XYZMove->ActorToMove || !XYZMove->ActorToMove->GetXYZAIController()) continue;

		AXYZAIController* Controller = XYZMove->ActorToMove->GetXYZAIController();
		AXYZActor* TargetActor = XYZMove->ActorToTarget;

		if(TargetActor)
		{
			Controller->XYZMoveToActor(TargetActor);
		}else
		{
			Controller->XYZMoveToLocation(XYZMove->TargetLocation);
		}
		MovesProcessed.Add(XYZMove);
		ProcessIndex++;
	}
	MovesToProcess = MovesToProcess.Difference(MovesProcessed);
}
