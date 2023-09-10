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
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AXYZActor::AXYZActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
    bReplicates = true;

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
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
    /*
    FVector Start = GetActorLocation();
    FVector ForwardVector = FVector(0, 0, -1); // Facing downwards in the Z-axis
    FVector End = ((ForwardVector * 2000.f) + Start); // 2000 is the distance of the ray; you can adjust as needed

    FHitResult HitResult;

    // Collision parameters
    FCollisionQueryParams CollisionParams;

    // Perform the line trace 
    // The true parameter means it will trace against visible objects
    // ECC_Visibility is what it is looking for during the trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

#if WITH_EDITOR
    // Debug Line in editor
    if (bHit)
    {
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
    }
    else
    {
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
    }
#endif

    // If we hit something, place the actor at the hit location
    if (bHit)
    {
        FVector NewLocation = HitResult.Location + 10.0f;
        NewLocation.X = Start.X; // Keep X coordinate unchanged
        NewLocation.Y = Start.Y; // Keep Y coordinate unchanged
        SetActorLocation(NewLocation);
    }
    */

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

    SelectionDecal->SetMaterial(0, DecalMaterials[DecalType]);
    if (bShowDecal) {
        SelectionDecal->DecalSize = FVector(400.0f, 80.0f, 80.0f);
    }
    else {
        SelectionDecal->DecalSize = FVector::ZeroVector;
    }
    SelectionDecal->MarkRenderStateDirty();
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
    for (AXYZActor* OtherActor : GameState->AllActors)
    {
        // Exclude self from the list (if it's in the list)
        if (!OtherActor || (OtherActor == this || bIgnoreFriendlyActors && OtherActor->TeamId == TeamId || OtherActor->Health <= 0.0f))
        {
            continue;
        }

        float DistanceSqr = FVector::DistSquaredXY(this->GetActorLocation(), OtherActor->GetActorLocation());

        if (DistanceSqr < ClosestDistanceSqr && DistanceSqr <= FMath::Square(AttackRange))
        {
            ClosestDistanceSqr = DistanceSqr;
            ClosestActor = OtherActor;
        }
    }

    return ClosestActor;
}

void StopMovement() {

}