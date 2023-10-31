#include "XYZDeathManager.h"
#include "DeathStruct.h"
#include "XYZActor.h"
#include "XYZActorCache.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "XYZPlayerController.h"
#include "XYZBlobManager.h"
#include "XYZBlob.h"
#include "XYZAIController.h"
#include "XYZBuilding.h"
#include "XYZMapManager.h"
#include "XYZResourceActor.h"
#include "Components/CapsuleComponent.h"

void UXYZDeathManager::QueueDeath(AXYZActor* Actor)
{
	if(!Actor) return;
	
	TSharedPtr<FDeathStruct> DeathStruct = MakeShared<FDeathStruct>(Actor, CurrentTime + 1.5f, CurrentTime + .75f);
	AXYZGameState* XYZGameState = GetWorld()->GetGameState<AXYZGameState>();
	AXYZGameMode* XYZGameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();

	UXYZActorCache* ActorCache = GetWorld()->GetAuthGameMode<AXYZGameMode>()->ActorCache;
	if(ActorCache)
	{
		ActorCache->RemoveActorCount(Actor->TeamId, Actor->ActorId);
	}
	
	for (AXYZPlayerController* XYZController : XYZGameMode->PlayerControllers)
	{
		if (XYZController)
		{
			XYZController->XYZActorDestroyed(Actor->UActorId);
		}
	}
	
	XYZGameState->ActorsByUID.Remove(Actor->UActorId);
	if(!Actor->IsA(AXYZResourceActor::StaticClass()))
	{
		XYZGameState->SupplyByTeamId[Actor->TeamId] -= Actor->SupplyCost;
		XYZGameState->SupplyByTeamId[Actor->TeamId + 2] -= Actor->SupplyGain;
		
		for (UXYZBlob* Blob : XYZGameMode->BlobManager->ActiveBlobs)
		{
			Blob->RemoveAgent(Actor);
		}
		Actor->GetXYZAIController()->UnPossess();
		Actor->GetXYZAIController()->XYZStopMovement();
	}

	if(Actor->IsA(AXYZBuilding::StaticClass()))
	{
		Cast<AXYZBuilding>(Actor)->ClearProduction();
	}
	
	Actor->GetCapsuleComponent()->SetCollisionProfileName("Ragdoll");
	Actor->bHasAvoidance = false;
	Actor->CurrentCapsuleRadius = 0.0f;
	Actor->CollisionName = "Ragdoll";
	Actor->SetState(EXYZUnitState::DEAD);
	Actor->TargetActor = nullptr;
	
	DeathQueue.Add(DeathStruct);
}

void UXYZDeathManager::Process(float DeltaSeconds)
{
	CurrentTime += DeltaSeconds;
	if(DeathQueue.IsEmpty()) return;
	TSet<TSharedPtr<FDeathStruct>> ActorsAlive;
	AXYZGameMode* XYZGameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();
	for(TSharedPtr<FDeathStruct> DeathStruct : DeathQueue)
	{
		if(!DeathStruct || !DeathStruct->Actor) continue;
		
		if(DeathStruct->TimeToRemoveVision <= CurrentTime && !DeathStruct->bRemovedVision)
		{
			XYZGameMode->MapManager->ActorsToRemove.Add(DeathStruct->Actor);
			DeathStruct->bRemovedVision = true;
		}
		if(DeathStruct->TimeToDie <= CurrentTime)
		{
			DeathStruct->Actor->Destroy();
		}else
		{
			ActorsAlive.Add(DeathStruct);
		}
	}
	DeathQueue = ActorsAlive;
}