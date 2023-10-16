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
	

public:
	//<ActorId, <UniqueActorId,XYZActor>>
    TSortedMap<int32, TMap<int32, AXYZActor*>> SelectedActors;
    TArray<TSortedMap<int32, TMap<int32, AXYZActor*>>> ControlGroups;
    UPROPERTY()
        class AXYZActor* SelectedEnemy;
    UPROPERTY()
        class AXYZActor* SelectedResource;
    UPROPERTY()
        int32 ActiveActor;
    UPROPERTY()
        int32 ActiveIndex;
    UPROPERTY()
        int32 Num;
public:
    void Add(AXYZActor* Actor);
    void Add(TArray<AXYZActor*> Actors);
    void Remove(AXYZActor* Actor);
    void Remove(int32 ActorUId);
    void Remove(TArray<AXYZActor*> Actors);
    bool Contains(AXYZActor* Actor);
    bool Contains(int32 ActorUId);

    UFUNCTION()
    void InitControlGroups(int32 ControlGroupCount);
    UFUNCTION()
    void SetControlGroup(int32 ControlGroupIndex);
    UFUNCTION()
    void AddToControlGroup(int32 ControlGroupIndex);
    UFUNCTION()
    void SelectControlGroup(int32 ControlGroupIndex);
    UFUNCTION()
    void RemoveFromControlGroups(int32 ActorUId, int32 ActorId);
    UFUNCTION(BlueprintCallable)
        TArray<int32> GetControlGroupAmounts();
    UFUNCTION(BlueprintCallable)
    TArray<int32> GetActiveUIDFromControlGroups();
    UFUNCTION()
        void CycleSelection();
    
    UFUNCTION()
    void SelectEnemyActor(AXYZActor* Actor);
    UFUNCTION()
    void SelectResource(AXYZActor* Resource);
    UFUNCTION()
    TArray<AXYZActor*> ToArray();
    UFUNCTION()
    TArray<int32> ToActorIdArray();
    UFUNCTION()
        TArray<int32> GetActiveActorIds();

    UFUNCTION()
    void Empty();
    UFUNCTION()
    bool IsEmpty();
    UFUNCTION()
    FString ToString() const;
};
