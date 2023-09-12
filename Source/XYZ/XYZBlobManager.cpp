#include "XYZBlobManager.h"
#include "XYZBlob.h"
#include "XYZBlobFactory.h"
#include "XYZAction.h"

void UXYZBlobManager::ProcessBlobs()
{
    for (UXYZBlob* Blob : ActiveBlobs)
    {
        Blob->ProcessBlob();
    }
}

void UXYZBlobManager::AddBlob(UXYZBlob* NewBlob)
{
    if (NewBlob->AgentsInBlob.Num() == 0) return;

    if (ActiveBlobs.Num() > 0) {
        TMap<UXYZBlob*, TArray<AXYZActor*>> AgentsToRemove;
        for (UXYZBlob* Blob : ActiveBlobs) {
            if (!Blob || Blob == NewBlob) continue;
            AgentsToRemove.Add(Blob, {});
            for (AXYZActor* Agent : NewBlob->AgentsInBlob) {
                if (Blob->AgentsInBlob.Contains(Agent)) {
                    AgentsToRemove[Blob].Add(Agent);
                }
            }
        }


        for (auto& Entry : AgentsToRemove)
        {
            UXYZBlob* Blob = Entry.Key;
            for (AXYZActor* Actor : Entry.Value) {
                Blob->AgentsInBlob.Remove(Actor);
            }
        }
    }
    
    ActiveBlobs.Add(NewBlob);
}

void UXYZBlobManager::RemoveInactiveBlobs()
{
    TArray<UXYZBlob*> BlobsToRemove;
    for (UXYZBlob* Blob : ActiveBlobs) {
        if (Blob->AgentsInBlob.Num() == 0) {
            BlobsToRemove.Add(Blob);
            Blob->ActionQueue.Empty();
            Blob->AgentsInBlob.Empty();
            Blob->CenterAgent = nullptr;
        }
    }
    for (UXYZBlob* Blob : BlobsToRemove) {
        ActiveBlobs.Remove(Blob);
    }
}

void UXYZBlobManager::QueueAction(UXYZAction* Action) {

    bool bIsBlobEqual = true;
    UXYZBlob* NewBlob = UXYZBlobFactory::CreateBlobFromAction(Action, NextBlobId);
    UXYZBlob* ExistingBlob = nullptr;

    if (ActiveBlobs.Num() > 0) {
        for (UXYZBlob* Blob : ActiveBlobs) {
            bIsBlobEqual = true;
            if (Blob->AgentsInBlob.Num() != Action->ActorSet.Num()) {
                bIsBlobEqual = false;
                continue;
            }
            for (AXYZActor* Agent : Blob->AgentsInBlob) {
                bIsBlobEqual = bIsBlobEqual && Action->ActorSet.Contains(Agent);
            }
            if (bIsBlobEqual) {
                ExistingBlob = Blob;
            }
        }
    }

    if (ExistingBlob && ExistingBlob->GetClass() == NewBlob->GetClass()) {
        if (!Action->bQueueInput) {
            ExistingBlob->bOverrideBlob = true;
            ExistingBlob->ActionQueue.Empty();
        }
        ExistingBlob->ActionQueue.Enqueue(Action);
        UE_LOG(LogTemp, Warning, TEXT("Existing Blob Enqueued Action"));
    }
    else {
        NewBlob->AgentsInBlob = Action->ActorSet;
        NewBlob->ActionQueue.Enqueue(Action);
        UE_LOG(LogTemp, Warning, TEXT("New Blob Enqueued Action"));
        NewBlob->BlobId = NextBlobId;
        NextBlobId++;
        AddBlob(NewBlob);
    }
}