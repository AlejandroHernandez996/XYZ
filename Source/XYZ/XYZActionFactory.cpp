// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZActionFactory.h"
#include "XYZAction.h"
#include "XYZAttackAction.h"
#include "XYZMoveAction.h"
#include "XYZStopAction.h"
#include "XYZInputType.h"
#include "XYZGameState.h"
#include "XYZActor.h"

UXYZAction* UXYZActionFactory::CreateAction(TArray<int32> _SelectedActors, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount, AXYZGameState* GameState)
{
    if (_SelectedActors.Num() == 0) return nullptr;

    UXYZAction* CreatedAction = nullptr;
    if (InputType == EXYZInputType::SECONDARY_INPUT) {
        FString f = "Move_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZMoveAction::StaticClass(), ActionName, GameState);
    }
    if (InputType == EXYZInputType::STOP) {
        FString f = "Stop_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZStopAction::StaticClass(), ActionName, GameState);
    }
    if (InputType == EXYZInputType::ATTACK_MOVE) {
        
        FString f = "Attack_Move_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        UXYZAttackAction* AttackAction = Cast<UXYZAttackAction>(MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZAttackAction::StaticClass(), ActionName, GameState));
        if (_TargetActor) {
            AttackAction->bIgnoreAllies = false;
            AttackAction->bIsAttackMove = false;
        }
        else {
            AttackAction->bIsAttackMove = true;
        }
        
        return AttackAction;
    }

   
    return CreatedAction;
}

UXYZAction* UXYZActionFactory::MakeAction(TArray<int32> _SelectedActors, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount, UClass* ActionClass, FName ActionName, AXYZGameState* GameState)
{
    UXYZAction* NewAction = NewObject<UXYZAction>(GetTransientPackage(), ActionClass, ActionName);
    if (NewAction)
    {
        NewAction->Initialize(_TargetActor, _TargetLocation, _bQueueInput);
        for (int i = 0; i < _SelectedActors.Num(); i++) {
            NewAction->ActorSet.Add(GameState->ActorsByUID[_SelectedActors[i]]);
        }
    }
    
    return NewAction;
}