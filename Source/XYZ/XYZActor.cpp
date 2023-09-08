// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"
#include "XYZAction.h"

// Sets default values
AXYZActor::AXYZActor()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AXYZActor::BeginPlay()
{
	Super::BeginPlay();
    TArray<UActorComponent*> DecalComponents = GetComponentsByClass(UDecalComponent::StaticClass());

    if (DecalComponents.Num() > 0) // Make sure there is at least one DecalComponent.
    {
        // Assuming you want the first DecalComponent found.
        SelectionDecal = Cast<UDecalComponent>(DecalComponents[0]);
    }
    else
    {
        // Handle case where no DecalComponent was found if needed.
        UE_LOG(LogTemp, Warning, TEXT("No DecalComponent found!"));
    }
}

// Called every frame
void AXYZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (GetLocalRole() == ROLE_Authority) {
        if (bCancelActionFlag && CurrentAction) {
            CurrentAction->CancelAction();
            bCancelActionFlag = false;
        }
        if (CurrentAction && !CurrentAction->IsFlaggedForDeuque()) {
            CurrentAction->TryAction(DeltaTime);
        }
        if (!ActionQueue.IsEmpty()) {
            if (!CurrentAction || CurrentAction->IsFlaggedForDeuque()) {
                PrevAction = CurrentAction;
                CurrentAction = ActionQueue[0];
                ActionQueue.RemoveAt(0);
            }
        }
        if (ActionQueue.Num() > 0) {
            UE_LOG(LogTemp, Warning, TEXT("QueueSize: %d, ActorName: %s"), ActionQueue.Num(), *GetName());
        }
    }
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

}

void AXYZActor::QueueAction(UXYZAction* Action) {
	if (!Action) return;

	if (!Action->bQueueInput) {
        if (CurrentAction) {
            bCancelActionFlag = true;
        }
		ActionQueue.Empty();
	}
	ActionQueue.Add(Action);

}

void AXYZActor::ShowDecal(bool bShowDecal) {
    if (bShowDecal) {
        SelectionDecal->DecalSize = FVector(400.0f, 80.0f, 80.0f);
    }
    else {
        SelectionDecal->DecalSize = FVector::ZeroVector;
    }
    SelectionDecal->MarkRenderStateDirty();
}