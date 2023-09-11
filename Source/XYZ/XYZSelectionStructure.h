// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZSelectionStructure.generated.h"

/**
 * 
 */
class AXYZActor;

UCLASS()
class XYZ_API UXYZSelectionStructure : public UObject
{
	GENERATED_BODY()
	

private:
	//<ActorId, <UniqueActorId,XYZActor>>
	TMap<int32, TMap<int32, AXYZActor*>> SelectedActors;
    TArray<TMap<int32, TMap<int32, AXYZActor*>>> ControlGroups;
    AXYZActor* SelectedEnemy;

public:

    void Add(AXYZActor* Actor);
    void Add(TArray<AXYZActor*> Actors);
    void Remove(AXYZActor* Actor);
    void Remove(int32 ActorUId);
    void Remove(TArray<AXYZActor*> Actors);

    void InitControlGroups(int32 ControlGroupCount);
    void SetControlGroup(int32 ControlGroupIndex);
    void AddToControlGroup(int32 ControlGroupIndex);
    void SelectControlGroup(int32 ControlGroupIndex);
    void RemoveFromControlGroups(int32 ActorUId);

    void SelectEnemyActor(AXYZActor* Actor);

    TArray<AXYZActor*> ToArray();
    TArray<int32> ToActorIdArray();

    bool Contains(AXYZActor* Actor);
    bool Contains(int32 ActorUId);

    void Empty();

    bool IsEmpty();

    FString ToString() const;

    int32 ActiveIndex;

public:
    int32 Num;

};
