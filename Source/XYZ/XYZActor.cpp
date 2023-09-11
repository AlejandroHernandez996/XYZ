// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZActor.h"
#include "XYZAction.h"
#include "XYZGameState.h"
#include "XYZDecalType.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "XYZAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AXYZActor::AXYZActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
    bReplicates = true;

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AXYZAIController::StaticClass();
}

void AXYZActor::BeginPlay()
{
	Super::BeginPlay();
    
    TArray<UActorComponent*> DecalComponents = GetComponentsByClass(UDecalComponent::StaticClass());
    SelectionDecal = Cast<UDecalComponent>(DecalComponents[0]);
   
}

void AXYZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (Health == 0.0f) {
        for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            AXYZPlayerController* PlayerController = Cast<AXYZPlayerController>(It->Get());
            if (PlayerController)
            {
                PlayerController->XYZActorDestroyed(UActorId);
            }
        }
        Destroy();
    }
    if (GetLocalRole() == ROLE_Authority) {

        if (ActionQueue.Num() > 0 && ActionQueue[0]) {
            if (ActionQueue[0]->IsFlaggedForDeuque()) {
                ActionQueue.RemoveAt(0);
            }
        }
        if (ActionQueue.Num() > 0 && ActionQueue[0]) {
            ActionQueue[0]->TryAction(DeltaTime);
        }
    }
}

void AXYZActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AXYZActor, Health);
    DOREPLIFETIME(AXYZActor, MaxHealth);
    DOREPLIFETIME(AXYZActor, MoveSpeed);
    DOREPLIFETIME(AXYZActor, BaseArmor);
    DOREPLIFETIME(AXYZActor, AttackDamage);
    DOREPLIFETIME(AXYZActor, AttackRate);
    DOREPLIFETIME(AXYZActor, AttackRange);

    DOREPLIFETIME(AXYZActor, UActorId);

}

void AXYZActor::QueueAction(UXYZAction* Action) {
	if (!Action) return;
    if (!Action->bQueueInput && ActionQueue.Num() > 0 && ActionQueue[0]) {
        ActionQueue[0]->CancelAction();
        ActionQueue.Empty();
    }
	ActionQueue.Add(Action);

}

void AXYZActor::ShowDecal(bool bShowDecal, EXYZDecalType DecalType) {

    if (!bShowDecal) {
        SelectionDecal->SetMaterial(0, DecalMaterials[EXYZDecalType::NEUTRAL]);
    }
    else {
        SelectionDecal->SetMaterial(0, DecalMaterials[DecalType]);
    }
    //SelectionDecal->MarkRenderStateDirty();
}

void AXYZActor::Attack(AXYZActor* TargetActor) {
    if (GetLocalRole() != ROLE_Authority) {
        return;
    }
    if (TargetActor && !bIsAttackOnCooldown) {
        bIsAttackOnCooldown = true;
        GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this]() {
            bIsAttackOnCooldown = false;
            }, AttackRate, false);
        TargetActor->Health -= AttackDamage;
        UE_LOG(LogTemp, Warning, TEXT("Attacking for %d enemy health %d"), AttackDamage, TargetActor->Health);
    }
}

AXYZActor* AXYZActor::FindClosestActor(bool bIgnoreFriendlyActors) {

    AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();

    AXYZActor* ClosestActor = nullptr;
    float ClosestDistanceSqr = FLT_MAX;
    for (AXYZActor* OtherActor : GameState->GetAllActors())
    {
        bool bTargetIsFriendlyAndShouldIgnore = OtherActor->TeamId == TeamId && bIgnoreFriendlyActors;
        if (!OtherActor || OtherActor == this || bTargetIsFriendlyAndShouldIgnore || OtherActor->Health <= 0.0f) {
            continue;
        }

        float DistanceSqr = FVector::DistSquaredXY(this->GetActorLocation(), OtherActor->GetActorLocation());

        if (DistanceSqr < ClosestDistanceSqr && DistanceSqr <= FMath::Square(VisionRange))
        {
            ClosestDistanceSqr = DistanceSqr;
            ClosestActor = OtherActor;
        }
    }

    return ClosestActor;
}