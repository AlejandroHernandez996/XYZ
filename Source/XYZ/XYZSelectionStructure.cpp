// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZSelectionStructure.h"
#include "Components/DecalComponent.h"
#include "XYZDecalType.h"
#include "XYZResourceActor.h"
#include "XYZActor.h"

void UXYZSelectionStructure::Add(AXYZActor* Actor) {
    // First check if ActorId already exists as a key in the map.
    if (SelectedActors.Contains(Actor->ActorId)) {
        // ActorId exists, so we check if UActorId already exists to avoid duplicates.
        if (!SelectedActors[Actor->ActorId].Contains(Actor->UActorId)) {
            // UActorId does not exist for this ActorId, so we can safely add it.
            SelectedActors[Actor->ActorId].Add(Actor->UActorId, Actor);
            UE_LOG(LogTemp, Warning, TEXT("Added Actor with existing ActorId."));
            Num++;
            Actor->ShowDecal(true, EXYZDecalType::FRIENDLY);
        }
    }
    else {
        if (SelectedActors.IsEmpty()) {
            ActiveIndex = 0;
            ActiveActor = Actor->ActorId;
        }
        // ActorId does not exist in the map, so create a new key-value pair.
        TMap<int32, AXYZActor*> InnerMap;
        InnerMap.Add(Actor->UActorId, Actor);
        SelectedActors.Add(Actor->ActorId, InnerMap);
        Actor->ShowDecal(true, EXYZDecalType::FRIENDLY);
        Num++;
        UE_LOG(LogTemp, Warning, TEXT("Added Actor with new ActorId."));
    }
}

void UXYZSelectionStructure::Add(TArray<AXYZActor*> Actors) {
    if (SelectedEnemy) {
        SelectedEnemy->ShowDecal(false, EXYZDecalType::ENEMY);
        SelectedEnemy = nullptr;
    }
    if (SelectedResource) {
        SelectedResource->ShowDecal(false, EXYZDecalType::RESOURCE);
        SelectedResource = nullptr;
    }
    
    for (auto Actor : Actors) {
        Add(Actor);
    }
}

void UXYZSelectionStructure::Remove(TArray<AXYZActor*> Actors) {
    for (auto Actor : Actors) {
        Remove(Actor);
    }
}

void UXYZSelectionStructure::Remove(int32 ActorUId)
{
    int32 KeyOfInnerMap = -1;
    for (auto& OuterElement : SelectedActors)
    {
        TMap<int32, AXYZActor*>& InnerMap = OuterElement.Value;
        if (InnerMap.Contains(ActorUId)) {
            InnerMap.Remove(ActorUId);
            if(InnerMap.Num() == 0) {
                OuterElement.Key = KeyOfInnerMap;
            }
            break;
        }
        
    }
    if (KeyOfInnerMap != -1) {
        SelectedActors.Remove(KeyOfInnerMap);
    }
    if (SelectedActors.IsEmpty()) {
        ActiveActor = -1;
        ActiveIndex = -1;
    }
}

void UXYZSelectionStructure::Remove(AXYZActor* Actor) {
    if (Contains(Actor)) {
        SelectedActors[Actor->ActorId].Remove(Actor->UActorId);
        UE_LOG(LogTemp, Warning, TEXT("Removed Actor"));
        Actor->ShowDecal(false, EXYZDecalType::FRIENDLY);
        Num--;
        if (SelectedActors[Actor->ActorId].Num() == 0) {
            SelectedActors.Remove(Actor->ActorId);
        }
    }
    if (SelectedActors.IsEmpty()) {
        ActiveActor = -1;
        ActiveIndex = -1;
    }
}

void UXYZSelectionStructure::InitControlGroups(int32 ControlGroupCount) {
    for (int i = 0; i < ControlGroupCount; i++) {
        TSortedMap <int32, TMap<int32, AXYZActor*>> ControlGroup;
        ControlGroups.Add(ControlGroup);
    }
}

void UXYZSelectionStructure::SetControlGroup(int32 ControlGroupIndex) {
    if (IsEmpty()) return;
    ControlGroups[ControlGroupIndex] = SelectedActors;
}

void UXYZSelectionStructure::AddToControlGroup(int32 ControlGroupIndex) {
    if (IsEmpty()) return;
    for (AXYZActor* Actor : ToArray()) {
        if (ControlGroups[ControlGroupIndex].Contains(Actor->ActorId)) {
            if (!ControlGroups[ControlGroupIndex][Actor->ActorId].Contains(Actor->UActorId)) {
                ControlGroups[ControlGroupIndex][Actor->ActorId].Add(Actor->UActorId, Actor);
            }
        }
        else {
            TMap<int32, AXYZActor*> InnerMap;
            InnerMap.Add(Actor->UActorId, Actor);
            ControlGroups[ControlGroupIndex].Add(Actor->ActorId, InnerMap);
        }
    }
}

void UXYZSelectionStructure::SelectControlGroup(int32 ControlGroupIndex) {
    if (ControlGroups[ControlGroupIndex].IsEmpty()) return;

    Empty();
    TArray<AXYZActor*> ResultArray;
    for (auto& KeyValPair : ControlGroups[ControlGroupIndex]) {
        for (auto& InnerKeyValPair : KeyValPair.Value) {
            ResultArray.Add(InnerKeyValPair.Value);
        }
    }
    Add(ResultArray);

}

void UXYZSelectionStructure::RemoveFromControlGroups(int32 ActorUId, int32 ActorId) {

    for (int i = 0; i < ControlGroups.Num(); i++) {
        if (ControlGroups[i].Contains(ActorId) && ControlGroups[i][ActorId].Contains(ActorUId)) {
            ControlGroups[i][ActorId].Remove(ActorUId);
            if (ControlGroups[i][ActorId].IsEmpty()) {
                ControlGroups[i].Remove(ActorId);
            }
        }
    }
}

void UXYZSelectionStructure::SelectEnemyActor(AXYZActor* Actor) {
    if (SelectedEnemy) {
        SelectedEnemy->ShowDecal(false, EXYZDecalType::ENEMY);
        SelectedEnemy = nullptr;
    }
    Empty();

    SelectedEnemy = Actor;
    Actor->ShowDecal(true, EXYZDecalType::ENEMY);
}

void UXYZSelectionStructure::SelectResource(AXYZActor* Resource) {
    if (SelectedResource) {
        SelectedResource->ShowDecal(false, EXYZDecalType::RESOURCE);
        SelectedResource = nullptr;
    }
    Empty();

    SelectedResource = Resource;
    Resource->ShowDecal(true, EXYZDecalType::RESOURCE);
}

TArray<AXYZActor*> UXYZSelectionStructure::ToArray() {
    TArray<AXYZActor*> ResultArray;
    if (SelectedActors.IsEmpty()) return ResultArray;

    for (auto& KeyValPair : SelectedActors) {
        for (auto& InnerKeyValPair : KeyValPair.Value) {
            ResultArray.Add(InnerKeyValPair.Value);
        }
    }

    return ResultArray;
}

TArray<int32> UXYZSelectionStructure::ToActorIdArray() {
    TArray<int32> ResultArray;

    for (auto& KeyValPair : SelectedActors) {
        for (auto& InnerKeyValPair : KeyValPair.Value) {
            ResultArray.Add(InnerKeyValPair.Value->UActorId);
        }
    }

    return ResultArray;
}

TArray<int32> UXYZSelectionStructure::GetActiveActorIds() {
    TArray<int32> ResultArray;
    if (ActiveIndex > -1 && ActiveActor > -1) {
        if (SelectedActors.Contains(ActiveActor)) {
            for (auto& InnerKeyValPair : SelectedActors[ActiveActor]) {
                ResultArray.Add(InnerKeyValPair.Value->UActorId);
            }
        }
    }
    return ResultArray;
}

bool UXYZSelectionStructure::Contains(AXYZActor* Actor) {
    return Actor && SelectedActors.Contains(Actor->ActorId) && SelectedActors[Actor->ActorId].Contains(Actor->UActorId);
}

bool UXYZSelectionStructure::Contains(int32 ActorUId) {
    for (const auto& OuterElement : SelectedActors)
    {
        const TMap<int32, AXYZActor*>& InnerMap = OuterElement.Value;

        if (InnerMap.Contains(ActorUId))
        {
            return true;
        }
    }
    return false;
}

void UXYZSelectionStructure::Empty() {
    if (SelectedEnemy) {
        SelectedEnemy->ShowDecal(false, EXYZDecalType::ENEMY);
        SelectedEnemy = nullptr;
    }
    if (SelectedResource) {
        SelectedResource->ShowDecal(false, EXYZDecalType::RESOURCE);
        SelectedResource = nullptr;
    }
    if (SelectedActors.IsEmpty()) return;

    TArray<AXYZActor*> Actors = ToArray();
    for (auto Actor : Actors) {
        if (Actor) {
            Actor->ShowDecal(false, EXYZDecalType::FRIENDLY);
        }
    }
    SelectedActors.Empty();
    ActiveActor = -1;
    ActiveIndex = -1;
    Num = 0;
}

bool UXYZSelectionStructure::IsEmpty() {
    return SelectedActors.IsEmpty();
}

void UXYZSelectionStructure::CycleSelection() {
    if (SelectedActors.IsEmpty()) return;

    ActiveIndex++;
    if (ActiveIndex >= SelectedActors.Num()) {
        ActiveIndex = 0;
    }
    TArray<int32> Keys;
    Keys.Reserve(SelectedActors.Num()); // Optional, but can optimize the allocation

    for (auto& Pair : SelectedActors)
    {
        Keys.Add(Pair.Key);
    }
    ActiveActor = Keys[ActiveIndex];
}
FString UXYZSelectionStructure::ToString() const {
    FString ResultString;

    for (const auto& OuterPair : SelectedActors) {
        ResultString += FString::Printf(TEXT("ActorId: %d => { "), OuterPair.Key);

        for (const auto& InnerPair : OuterPair.Value) {
            ResultString += FString::Printf(TEXT("(UniqueActorId: %d, ActorName: %s), "), InnerPair.Key, *InnerPair.Value->GetName());
        }

        ResultString += "}, ";
    }

    return ResultString;
}

TArray<int32> UXYZSelectionStructure::GetControlGroupAmounts() {
    TArray<int32> Amounts;
    for (const TSortedMap<int32, TMap<int32, AXYZActor*>>& SortedMap : ControlGroups)
    {
        int32 CurrentCount = 0;

        TArray<TMap<int32, AXYZActor*>> Actors;
        SortedMap.GenerateValueArray(Actors);
        for (auto& InnerMap: Actors)
        {
            CurrentCount += InnerMap.Num();
        }
        Amounts.Add(CurrentCount);
    }
    return Amounts;
}

TArray<int32> UXYZSelectionStructure::GetActiveUIDFromControlGroups() {
    TArray<int32> ActiveActorUIDs;
    for (const TSortedMap<int32, TMap<int32, AXYZActor*>>& SortedMap : ControlGroups)
    {
        TArray<TMap<int32, AXYZActor*>> Actors;
        SortedMap.GenerateValueArray(Actors);
        int32 FoundActorUID = -1;
        for (auto& InnerMap: Actors)
        {
            TArray<AXYZActor*> FoundActors;
            InnerMap.GenerateValueArray(FoundActors);

            for(AXYZActor* FoundActor : FoundActors)
            {
                if(FoundActor)
                {
                    FoundActorUID = FoundActor->UActorId;
                    break;
                }
            }
            if(FoundActorUID != -1)
            {
                break;
            }
        }
        ActiveActorUIDs.Add(FoundActorUID);
    }
    return ActiveActorUIDs;
}