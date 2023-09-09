// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZSelectionStructure.h"
#include "Components/DecalComponent.h"
#include "XYZActor.h"

void UXYZSelectionStructure::Add(AXYZActor* Actor) {
    // First check if ActorId already exists as a key in the map.
    if (SelectedActors.Contains(Actor->ActorId)) {
        // ActorId exists, so we check if UActorId already exists to avoid duplicates.
        if (!SelectedActors[Actor->ActorId].Contains(Actor->UActorId)) {
            // UActorId does not exist for this ActorId, so we can safely add it.
            SelectedActors[Actor->ActorId].Add(Actor->UActorId, Actor);
            UE_LOG(LogTemp, Warning, TEXT("Added Actor with existing ActorId."));
            Actor->ShowDecal(true);
        }
    }
    else {
        // ActorId does not exist in the map, so create a new key-value pair.
        TMap<int32, AXYZActor*> InnerMap;
        InnerMap.Add(Actor->UActorId, Actor);
        SelectedActors.Add(Actor->ActorId, InnerMap);
        Actor->ShowDecal(true);
        UE_LOG(LogTemp, Warning, TEXT("Added Actor with new ActorId."));
    }
}

void UXYZSelectionStructure::Add(TArray<AXYZActor*> Actors) {
    for (auto Actor : Actors) {
        Add(Actor);
    }
}

void UXYZSelectionStructure::Remove(TArray<AXYZActor*> Actors) {
    for (auto Actor : Actors) {
        Remove(Actor);
    }
}

void UXYZSelectionStructure::Remove(AXYZActor* Actor) {
    // First check if ActorId already exists as a key in the map.
    if (Contains(Actor)) {
        SelectedActors[Actor->ActorId].Remove(Actor->UActorId);
        UE_LOG(LogTemp, Warning, TEXT("Removed Actor"));

        // Optionally, remove the ActorId key if it has an empty map as a value.
        if (SelectedActors[Actor->ActorId].Num() == 0) {
            SelectedActors.Remove(Actor->ActorId);
            Actor->ShowDecal(false);
        }
    }
}

void UXYZSelectionStructure::InitControlGroups(int32 ControlGroupCount) {
    for (int i = 0; i < ControlGroupCount; i++) {
        TMap <int32, TMap<int32, AXYZActor*>> ControlGroup;
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
            ResultArray.Add(InnerKeyValPair.Value->ActorId);
        }
    }

    return ResultArray;
}

bool UXYZSelectionStructure::Contains(AXYZActor* Actor) {
    return Actor && SelectedActors.Contains(Actor->ActorId) && SelectedActors[Actor->ActorId].Contains(Actor->UActorId);
}

void UXYZSelectionStructure::Empty() {
    if (SelectedActors.IsEmpty()) return;

    TArray<AXYZActor*> Actors = ToArray();
    for (auto Actor : Actors) {
        if (Actor) {
            Actor->ShowDecal(false);
        }
    }
    SelectedActors.Empty();
}

bool UXYZSelectionStructure::IsEmpty() {
    return SelectedActors.IsEmpty();
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

