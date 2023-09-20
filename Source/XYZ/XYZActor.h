// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XYZAbility.h"
#include "XYZFactionType.h"
#include "XYZDecalType.h"
#include "XYZUnitState.h"
#include "XYZActor.generated.h"

UCLASS()
class XYZ_API AXYZActor : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXYZActor();

public:	
	virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        int32 ActorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", Replicated)
        int32 UActorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        int32 TeamId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", Replicated)
        EXYZUnitState State = EXYZUnitState::IDLE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        EXYZUnitState PreviousState = EXYZUnitState::IDLE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
        EXYZFactionType Faction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", Replicated)
        float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", Replicated)
        float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", Replicated)
        float MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", Replicated)
        int32 BaseArmor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Replicated)
        int32 AttackDamage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Replicated)
        float AttackRate;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Replicated)
        float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
        float VisionRange;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decal")
        TMap<EXYZDecalType, UMaterialInterface*> DecalMaterials;

    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
        TArray<UXYZAbility*> Abilities;

    UPROPERTY()
    TArray<UXYZAction*> ActionQueue;
    UPROPERTY()
    UXYZAction* CurrentAction;
    UPROPERTY()
    UXYZAction* PrevAction;

    UFUNCTION()
        void Attack();
    UPROPERTY()
        FTimerHandle AttackTimer;
    UPROPERTY()
        bool bIsAttackOnCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
        UDecalComponent* SelectionDecal;

    UFUNCTION()
    void ShowDecal(bool bShowDecal, EXYZDecalType DecalType);

    UFUNCTION()
        void QueueAction(UXYZAction* Action);
    UFUNCTION()
        AXYZActor* FindClosestActor(bool bIgnoreFriendlyActors);
    UFUNCTION()
        void SetState(EXYZUnitState UnitState);

    bool bCancelActionFlag;
    bool bCanMove = true;

    float InitialCapsuleRadius;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        class AXYZAIController* XYZAIController;
    UFUNCTION()
        class AXYZAIController* GetXYZAIController();
    UFUNCTION()
        void ScanXYZActorsAhead();
    UFUNCTION()
        AXYZActor* ScanAndPush(FVector Start, FVector End, TSet<AXYZActor*> ActorsFound);
    UPROPERTY()
        FVector TargetLocation;
    UPROPERTY()
        AXYZActor* TargetActor;
    UPROPERTY()
        bool bIsAggresive = true;
    UFUNCTION()
        void AttackMoveTarget();
};