#include "XYZBlobFactory.h"
#include "XYZSimpleMovingBlob.h"
#include "XYZSimpleAttackMovingBlob.h"
#include "XYZSimpleAttackTargetBlob.h"
#include "XYZSimpleFollowBlob.h"
#include "XYZStoppingBlob.h"  
#include "XYZStopAction.h"  
#include "XYZMoveAction.h"  
#include "XYZAttackAction.h"

UXYZBlob* UXYZBlobFactory::CreateBlobFromAction(const UXYZAction* Action, int32 BlobId)
{
    if (Action->IsA<UXYZMoveAction>())
    {
        if (Action->TargetActor) {
            if (Action->TargetActor->TeamId == Action->ActorSet.Array()[0]->TeamId) {
                FName BlobName(*("SimpleFollowBlob" + FString::FromInt(BlobId)));
                UXYZSimpleFollowBlob* NewBlob = NewObject<UXYZSimpleFollowBlob>(UXYZSimpleMovingBlob::StaticClass(), BlobName);
                NewBlob->TargetLocation = Action->TargetLocation;
                NewBlob->TargetActor = Action->TargetActor;
                return NewBlob;
            }
            else {
                FName BlobName(*("SimpleAttackTargetBlob" + FString::FromInt(BlobId)));
                UXYZSimpleAttackTargetBlob* NewBlob = NewObject<UXYZSimpleAttackTargetBlob>(UXYZSimpleAttackTargetBlob::StaticClass(), BlobName);
                NewBlob->TargetLocation = Action->TargetLocation;
                NewBlob->TargetActor = Action->TargetActor;
                return NewBlob;
            }
        }
        else {
            FName BlobName(*("SimpleMovingBlob_" + FString::FromInt(BlobId)));
            UXYZSimpleMovingBlob* NewBlob = NewObject<UXYZSimpleMovingBlob>(UXYZSimpleMovingBlob::StaticClass(), BlobName);
            NewBlob->TargetLocation = Action->TargetLocation;
            return NewBlob;
        }
    }
    if (Action->IsA<UXYZStopAction>())
    {
        FName BlobName(*("StoppingBlob_" + FString::FromInt(BlobId)));
        UXYZBlob* NewBlob = NewObject<UXYZStoppingBlob>(UXYZStoppingBlob::StaticClass(), BlobName);
        return NewBlob;
    }
    if (Action->IsA<UXYZAttackAction>())
    {
        if (Action->TargetActor) {
            FName BlobName(*("SimpleAttackTargetBlob" + FString::FromInt(BlobId)));
            UXYZSimpleAttackTargetBlob* NewBlob = NewObject<UXYZSimpleAttackTargetBlob>(UXYZSimpleAttackTargetBlob::StaticClass(), BlobName);
            NewBlob->TargetLocation = Action->TargetLocation;
            NewBlob->TargetActor = Action->TargetActor;
            return NewBlob;
        }
        else {
            FName BlobName(*("SimpleAttackingMovingBlob_" + FString::FromInt(BlobId)));
            UXYZSimpleAttackMovingBlob* NewBlob = NewObject<UXYZSimpleAttackMovingBlob>(UXYZSimpleAttackMovingBlob::StaticClass(), BlobName);
            NewBlob->TargetLocation = Action->TargetLocation;
            return NewBlob;
        }
    }
    return nullptr;
}