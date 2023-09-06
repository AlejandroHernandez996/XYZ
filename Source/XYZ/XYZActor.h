// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZAbility.h"
#include "XYZFactionType.h"
#include "XYZActor.generated.h"

UCLASS()
class XYZ_API AXYZActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXYZActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        int32 ActorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        int32 UActorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        int32 TeamId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        EXYZFactionType Faction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
        float MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
        int32 BaseArmor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
        int32 AttackDamage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
        float AttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
        float AttackRate;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
        float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
        TArray<UXYZAbility*> Abilities;

};
