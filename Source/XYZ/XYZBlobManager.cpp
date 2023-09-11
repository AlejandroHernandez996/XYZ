#include "XYZBlobManager.h"
#include "XYZBlob.h"

void UXYZBlobManager::ProcessBlobs()
{
    for (auto& Entry : ActiveBlobs)
    {
        Entry.Value->ProcessBlob();
    }
}

void UXYZBlobManager::AddBlob(UXYZBlob* Blob)
{
    ActiveBlobs.Add(NextBlobId, Blob);
    Blob->BlobId = NextBlobId;
    NextBlobId++;
}