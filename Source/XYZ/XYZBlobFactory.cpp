#include "XYZBlobFactory.h"
#include "XYZSimpleMovingBlob.h"
#include "XYZMoveAction.h"  // Assuming this exists

UXYZBlob* UXYZBlobFactory::CreateBlobFromAction(const UXYZAction* Action, int32 BlobId)
{
    if (Action->IsA<UXYZMoveAction>())
    {
        FName BlobName(*("SimpleMovingBlob_" + FString::FromInt(BlobId)));
        UXYZSimpleMovingBlob* NewBlob = NewObject<UXYZSimpleMovingBlob>(UXYZSimpleMovingBlob::StaticClass(), BlobName);
        NewBlob->TargetLocation = Action->TargetLocation; 
        return NewBlob;
    }

    return nullptr;
}