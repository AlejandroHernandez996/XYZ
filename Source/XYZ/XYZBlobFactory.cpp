#include "XYZBlobFactory.h"

UXYZBlob* UXYZBlobFactory::CreateBlobFromAction(const UXYZAction* Action, int32 BlobId)
{
    UXYZBlob* Blob = nullptr;

    if (Action) {
        FName BlobName(*("Blob_" + FString::FromInt(BlobId)));
        Blob = NewObject<UXYZBlob>(UXYZBlob::StaticClass(), BlobName);
        Blob->AgentsInBlob = Action->ActorSet;
        Blob->InitializeBlob();
    }
    return Blob;
}