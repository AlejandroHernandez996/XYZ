#include "XYZBlobFactory.h"
#include "XYZSimpleMovingBlob.h"
#include "XYZMoveAction.h"  // Assuming this exists

UXYZBlob* UXYZBlobFactory::CreateBlobFromAction(const UXYZAction* Action)
{
    if (Action->IsA<UXYZMoveAction>())
    {
        UXYZSimpleMovingBlob* NewBlob = NewObject<UXYZSimpleMovingBlob>(UXYZSimpleMovingBlob::StaticClass(), "SimpleMovingBlob");
        NewBlob->TargetLocation = Action->TargetLocation; 
        return NewBlob;
    }

    return nullptr;
}