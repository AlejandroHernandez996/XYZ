#include "XYZBlobFactory.h"
#include "XYZSimpleMovingBlob.h"
#include "XYZSimpleAttackMovingBlob.h"
#include "XYZStoppingBlob.h"  
#include "XYZStopAction.h"  
#include "XYZMoveAction.h"  
#include "XYZAttackAction.h"

UXYZBlob* UXYZBlobFactory::CreateBlobFromAction(const UXYZAction* Action, int32 BlobId)
{
    if (Action->IsA<UXYZMoveAction>())
    {
        FName BlobName(*("SimpleMovingBlob_" + FString::FromInt(BlobId)));
        UXYZSimpleMovingBlob* NewBlob = NewObject<UXYZSimpleMovingBlob>(UXYZSimpleMovingBlob::StaticClass(), BlobName);
        NewBlob->TargetLocation = Action->TargetLocation; 
        NewBlob->bAttackMove = false;
        return NewBlob;
    }
    if (Action->IsA<UXYZStopAction>())
    {
        FName BlobName(*("StoppingBlob_" + FString::FromInt(BlobId)));
        UXYZBlob* NewBlob = NewObject<UXYZStoppingBlob>(UXYZStoppingBlob::StaticClass(), BlobName);
        return NewBlob;
    }
    if (Action->IsA<UXYZAttackAction>())
    {
        FName BlobName(*("SimpleMovingBlob_" + FString::FromInt(BlobId)));
        UXYZSimpleMovingBlob* NewBlob = NewObject<UXYZSimpleMovingBlob>(UXYZSimpleMovingBlob::StaticClass(), BlobName);
        NewBlob->TargetLocation = Action->TargetLocation;
        NewBlob->bAttackMove = true;
        return NewBlob;
    }
    return nullptr;
}