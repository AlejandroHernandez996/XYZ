// Fill out your copyright notice in the Description page of Project Settings.
#include "XYZActionFactory.h"
#include "XYZAction.h"
#include "XYZAttackAction.h"
#include "XYZAbilityAction.h"
#include "XYZMoveAction.h"
#include "XYZStopAction.h"
#include "XYZHoldAction.h"
#include "XYZGatherAction.h"
#include "XYZInputType.h"
#include "XYZFollowAction.h"
#include "XYZGameState.h"
#include "XYZActor.h"
#include "XYZResourceActor.h"

UXYZAction* UXYZActionFactory::CreateAction(TArray<int32> _SelectedActors, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount, AXYZGameState* GameState, int32 ActiveActorId, int32 AbilityIndex)
{
    if (_SelectedActors.Num() == 0) return nullptr;
    bool bAreSelectedSameTeamAsTarget = false;

    if (_TargetActor) {
        bAreSelectedSameTeamAsTarget = _TargetActor->TeamId == GameState->ActorsByUID[_SelectedActors[0]]->TeamId;
    }
    UXYZAction* CreatedAction = nullptr;
    if (InputType == EXYZInputType::SECONDARY_INPUT) {
        if (_TargetActor) {
            if (_TargetActor->IsA(AXYZResourceActor::StaticClass())) {
                FString f = "Gather_Action_" + FString::FromInt(ActionCount);
                FName ActionName = FName(*f);
                CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZGatherAction::StaticClass(), ActionName, GameState);
            }
            else if (bAreSelectedSameTeamAsTarget) {
                FString f = "Follow_Action_" + FString::FromInt(ActionCount);
                FName ActionName = FName(*f);
                CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZFollowAction::StaticClass(), ActionName, GameState);
            }
            else {
                FString f = "Attack_Action_" + FString::FromInt(ActionCount);
                FName ActionName = FName(*f);
                CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZAttackAction::StaticClass(), ActionName, GameState);
            }
        }
        else {
            FString f = "Move_Action_" + FString::FromInt(ActionCount);
            FName ActionName = FName(*f);
            CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZMoveAction::StaticClass(), ActionName, GameState);
        }
    }
    if (InputType == EXYZInputType::STOP) {
        FString f = "Stop_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZStopAction::StaticClass(), ActionName, GameState);
    }
    if (InputType == EXYZInputType::ATTACK_MOVE) {
        FString f = "Attack_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZAttackAction::StaticClass(), ActionName, GameState);
    }
    if (InputType == EXYZInputType::HOLD) {
        FString f = "Hold_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZHoldAction::StaticClass(), ActionName, GameState);
    }
    if (InputType == EXYZInputType::ABILITY) {
        FString f = "Ability_Action_" + FString::FromInt(ActionCount);
        FName ActionName = FName(*f);
        CreatedAction = MakeAction(_SelectedActors, _TargetActor, _TargetLocation, _bQueueInput, InputType, ActionCount, UXYZAbilityAction::StaticClass(), ActionName, GameState);
        Cast<UXYZAbilityAction>(CreatedAction)->AbilityIndex = AbilityIndex;
        Cast<UXYZAbilityAction>(CreatedAction)->ActiveActorId = ActiveActorId;
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
            if(GameState->ActorsByUID.Contains(_SelectedActors[i]))
            {
                NewAction->ActorSet.Add(GameState->ActorsByUID[_SelectedActors[i]]);
            }
        }
    }
    
    return NewAction;
}