#include "XYZBlobManager.h"
#include "XYZBlob.h"
#include "XYZBlobFactory.h"
#include "XYZAction.h"

void UXYZBlobManager::Process(float DeltaSeconds)
{
    for (; ActionIndex < Actions.Num(); ActionIndex++) {
        QueueAction(Actions[ActionIndex]);
    }
    for (UXYZBlob* Blob : ActiveBlobs)
    {
        if (Blob) {
            Blob->Process(DeltaSeconds);
        }
    }
    RemoveInactiveBlobs();
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
                Blob->RemoveAgent(Actor);
            }
        }
    }
    
    ActiveBlobs.Add(NewBlob);
}

void UXYZBlobManager::RemoveInactiveBlobs()
{
    TArray<UXYZBlob*> BlobsToRemove;
    for (UXYZBlob* Blob : ActiveBlobs) {
        if (Blob->AgentsInBlob.Num() == 0 || Blob->Tail->QueuedAgents.Num() == Blob->AgentsInBlob.Num()) {
            BlobsToRemove.Add(Blob);
            Blob->InitializeBlob();
            Blob->AgentsInBlob.Empty();
        }
    }
    for (UXYZBlob* Blob : BlobsToRemove) {
        ActiveBlobs.Remove(Blob);
        UE_LOG(LogTemp, Warning, TEXT("Removed Blob"));
    }
}

void UXYZBlobManager::QueueAction(UXYZAction* Action) {

    bool bIsBlobEqual = true;
    UXYZBlob* NewBlob = UXYZBlobFactory::CreateBlobFromAction(Action, NextBlobId);
    if (!NewBlob) return;
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
            ExistingBlob->InitializeBlob();
        }
        ExistingBlob->AddAction(Action);
        UE_LOG(LogTemp, Warning, TEXT("Existing Blob Enqueued Action"));
    }
    else {
        NewBlob->AgentsInBlob = Action->ActorSet;
        NewBlob->AddAction(Action);
        UE_LOG(LogTemp, Warning, TEXT("New Blob Enqueued Action"));
        NewBlob->BlobId = NextBlobId;
        NextBlobId++;
        AddBlob(NewBlob);
    }
}