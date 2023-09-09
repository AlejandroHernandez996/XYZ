// XYZActionFactory.h

#pragma once

#include "CoreMinimal.h"
#include "XYZAction.h"
#include "XYZMoveAction.h"
#include "XYZStopAction.h"
#include "XYZAttackAction.h"
#include "XYZInputType.h"
#include "XYZActionFactory.generated.h"

UCLASS()
class XYZ_API UXYZActionFactory : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Action")
        static UXYZAction* CreateAction(AXYZActor* _Actor, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount)
    {
        if(InputType == EXYZInputType::SECONDARY_INPUT){
            FString f = "Move_Action_" + FString::FromInt(ActionCount);
            FName ActionName = FName(*f);
            UXYZAction* NewAction = NewObject<UXYZAction>(GetTransientPackage(), UXYZMoveAction::StaticClass(), ActionName);
            if (NewAction)
            {
                NewAction->Initialize(_Actor, _TargetActor, _TargetLocation, _bQueueInput);
            }
            return NewAction;
        }
        if (InputType == EXYZInputType::STOP) {
            FString f = "Stop_Action_" + FString::FromInt(ActionCount);
            FName ActionName = FName(*f);
            UXYZAction* NewAction = NewObject<UXYZAction>(GetTransientPackage(), UXYZStopAction::StaticClass(), ActionName);
            if (NewAction)
            {
                NewAction->Initialize(_Actor, _TargetActor, _TargetLocation, _bQueueInput);
            }
            return NewAction;
        }
        if (InputType == EXYZInputType::ATTACK_MOVE) {
            if (!_Actor) return nullptr;
            FString f = "Attack_Move_Action_" + FString::FromInt(ActionCount);
            FName ActionName = FName(*f);
            UXYZAction* NewAction = NewObject<UXYZAction>(GetTransientPackage(), UXYZAttackAction::StaticClass(), ActionName);
            if (NewAction)
            {
                NewAction->Initialize(_Actor, _TargetActor, _TargetLocation, _bQueueInput);
            }
            return NewAction;
        }
        return nullptr;
    }
};