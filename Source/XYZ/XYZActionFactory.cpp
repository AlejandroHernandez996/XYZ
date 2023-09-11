// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZActionFactory.h"
#include "XYZAction.h"
#include "XYZAttackAction.h"
#include "XYZMoveAction.h"
#include "XYZStopAction.h"
#include "XYZInputType.h"
#include "XYZActor.h"

UXYZAction* UXYZActionFactory::CreateAction(AXYZActor* _Actor, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount)
{
    if (!_Actor) return nullptr;

    if (InputType == EXYZInputType::SECONDARY_INPUT) {
        if (!_TargetActor || _Actor->TeamId == _TargetActor->TeamId) {
            FString f = "Move_Action_" + FString::FromInt(ActionCount);
            FName ActionName = FName(*f);
            return MakeAction(_Actor, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZMoveAction::StaticClass(), ActionName);
        }
        else {
            FString f = "Attack_Move_Action_" + FString::FromInt(ActionCount);
            FName ActionName = FName(*f);
            UXYZAction* AttackMoveAction =  MakeAction(_Actor, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZAttackAction::StaticClass(), ActionName);
            Cast<UXYZAttackAction>(AttackMoveAction)->bIsAttackMove = false;
            return AttackMoveAction;
        }
    }
    if (InputType == EXYZInputType::STOP) {
        FString f = "Stop_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        return MakeAction(_Actor, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZStopAction::StaticClass(), ActionName);
    }
    if (InputType == EXYZInputType::ATTACK_MOVE) {
        
        FString f = "Attack_Move_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        UXYZAttackAction* AttackAction = Cast<UXYZAttackAction>(MakeAction(_Actor, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZAttackAction::StaticClass(), ActionName));
        if (_TargetActor == _Actor) {
            AttackAction->TargetActor = nullptr;
        }
        if (_TargetActor) {
            AttackAction->bIgnoreAllies = false;
            AttackAction->bIsAttackMove = false;
        }
        else {
            AttackAction->bIsAttackMove = true;
        }
        
        return AttackAction;
    }
    return nullptr;
}

UXYZAction* UXYZActionFactory::MakeAction(AXYZActor* _Actor, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount, UClass* ActionClass, FName ActionName)
{
    UXYZAction* NewAction = NewObject<UXYZAction>(GetTransientPackage(), ActionClass, ActionName);
    if (NewAction)
    {
        NewAction->Initialize(_Actor, _TargetActor, _TargetLocation, _bQueueInput);
    }
    return NewAction;
}