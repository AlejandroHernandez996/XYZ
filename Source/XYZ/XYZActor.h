// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "GameFramework/Character.h"
#include "XYZAbility.h"
#include "XYZFactionType.h"
#include "XYZDecalType.h"
#include "XYZUnitState.h"
#include "XYZAnimMontageType.h"
#include "XYZActor.generated.h"

UCLASS()
class XYZ_API AXYZActor : public ACharacter, public IProcessable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXYZActor();

public:	
	virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    UPROPERTY()
    FVector LastLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", Replicated)
        int32 ActorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", Replicated)
        int32 UActorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", Replicated)
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
        TArray<TSubclassOf<class UXYZAbility>> AbilityTemplates;
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
        TArray<class UXYZAbility*> Abilities;
    UFUNCTION()
        void UseAbility(int32 Index);

    UPROPERTY()
    TArray<class UXYZAction*> ActionQueue;
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
    virtual void ShowDecal(bool bShowDecal, EXYZDecalType DecalType);

    UFUNCTION()
        AXYZActor* FindClosestActor(bool bIgnoreFriendlyActors);
    UFUNCTION()
        virtual void SetState(EXYZUnitState UnitState);

    bool bCancelActionFlag;
    bool bCanMove = true;

    float InitialCapsuleRadius;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", Replicated)
    float CurrentCapsuleRadius;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", Replicated)
        bool bHasAvoidance;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", Replicated)
        FName CollisionName;

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
    mutable AXYZActor* TargetActor;
    UPROPERTY()
        bool bIsAggresive = true;
    UFUNCTION()
        void AttackMoveTarget();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        int32 SupplyCost;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        int32 SupplyGain;

    UPROPERTY()
        class UXYZBlob* CurrentBlob;

    UPROPERTY(EditAnywhere)
        TMap<EXYZAnimMontageType, class UAnimMontage*> AnimMontageMap;
    
    UFUNCTION()
        void PlayAnimationMontage(EXYZAnimMontageType AnimMontageType);

    UPROPERTY()
    FIntVector2 GridCoord;

    virtual void Process(float DeltaSeconds);

    UPROPERTY()
    bool bIsVisible = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    TArray<UMaterialInstance*> TeamColors;
    UPROPERTY()
    bool bSetTeamColor = false;
    UFUNCTION()
    void SetTeamColor();

    UFUNCTION()
    int GetActorPriority(const AXYZActor* Actor);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
    FVector TargetActorLocationReplicated;
};