// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYZPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "DrawDebugHelpers.h"
#include "XYZSelectionStructure.h"
#include "Kismet/GameplayStatics.h" // Include this header
#include "XYZHUD.h"
#include "EnhancedInputSubsystems.h"

AXYZPlayerController::AXYZPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Initialize the InputTriggeredTime map with default values
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
		EnumValue <= static_cast<int32>(EXYZInputType::STOP);
		EnumValue++)
	{
		InputTriggeredTime.Add(static_cast<EXYZInputType>(EnumValue), 0.0f);
	}
	InputTriggeredCooldown = .16f;
	SelectionStructure = NewObject<UXYZSelectionStructure>(this, UXYZSelectionStructure::StaticClass(), "SelectionStructure");
	PrimaryActorTick.bCanEverTick = true;
}

void AXYZPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AXYZPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	float x, y;
	if (!GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y)) {
		OnSelectionBoxReleased.Broadcast(0, 0);
	}

	bWorldHitSuccessful = GetHitResultAtScreenPosition(GetMousePositionOnViewport(), ECollisionChannel::ECC_WorldStatic, true, WorldHit);
	bXYZActorHitSuccessful = GetHitResultAtScreenPosition(GetMousePositionOnViewport(), ECollisionChannel::ECC_WorldStatic, true, XYZActorHit);
}

void AXYZPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::PRIMARY_INPUT);
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::PRIMARY_INPUT);
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::PRIMARY_INPUT);
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::PRIMARY_INPUT);

		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::SECONDARY_INPUT);
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::SECONDARY_INPUT);
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::SECONDARY_INPUT);
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::SECONDARY_INPUT);

		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::ATTACK_MOVE);
		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::ATTACK_MOVE);
		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::ATTACK_MOVE);
		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::ATTACK_MOVE);

		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::STOP);
		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::STOP);
		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::STOP);
		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::STOP);

		EnhancedInputComponent->BindAction(PrimaryModifierInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::PRIMARY_MOD);
		EnhancedInputComponent->BindAction(PrimaryModifierInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::PRIMARY_MOD);

		EnhancedInputComponent->BindAction(SecondaryModifierInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::SECONDARY_MOD);
		EnhancedInputComponent->BindAction(SecondaryModifierInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::SECONDARY_MOD);

		for (int32 i = 0; i < ControlGroupInputActions.Num(); i++) {
			EnhancedInputComponent->BindAction(ControlGroupInputActions[i], ETriggerEvent::Started, this, &AXYZPlayerController::OnControlGroupInputStarted, i);
		}
		SelectionStructure->InitControlGroups(ControlGroupInputActions.Num());
	}
}

void AXYZPlayerController::OnControlGroupInputStarted(int32 ControlGroupIndex) {
	if (bPrimaryModifier) {
		SelectionStructure->AddToControlGroup(ControlGroupIndex);
	}
	else if (bSecondaryModifier) {
		SelectionStructure->SetControlGroup(ControlGroupIndex);
	}
	else {
		SelectionStructure->SelectControlGroup(ControlGroupIndex);
	}
}

void AXYZPlayerController::OnInputStarted(EXYZInputType InputType)
{
	InputTriggeredTime[InputType] = 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("Input Started for Type %d"), static_cast<int32>(InputType));
	FXYZInputMessage InputMessage;
	switch (InputType) {
		case EXYZInputType::PRIMARY_INPUT:
			BoxSelectStart = GetMousePositionOnViewport();
			GetHUD<AXYZHUD>()->bSelectActors = true;
			GetHUD<AXYZHUD>()->BoxStart = BoxSelectStart;
			GetHUD<AXYZHUD>()->BoxEnd = BoxSelectStart;
			// Fire the SelectionBox event
			OnSelectionBox.Broadcast(BoxSelectStart.X, BoxSelectStart.Y);
			break;
		case EXYZInputType::PRIMARY_MOD:
			bPrimaryModifier = true;
			break;
		case EXYZInputType::SECONDARY_MOD:
			bSecondaryModifier = true;
			break;
		case EXYZInputType::STOP:
			InputMessage = FXYZInputMessage(0, SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, false);
			QueueInput(InputMessage);
			break;
		case EXYZInputType::ATTACK_MOVE:
			AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
			int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
			InputMessage = FXYZInputMessage(0, SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, InputType, bPrimaryModifier);
			QueueInput(InputMessage);
			break;
	}
}

// Triggered every frame when the input is held down
void AXYZPlayerController::OnInputTriggered(EXYZInputType InputType)
{
	InputTriggeredTime[InputType] += GetWorld()->GetDeltaSeconds();

	if (InputType == EXYZInputType::PRIMARY_INPUT) {
		BoxSelectEnd = GetMousePositionOnViewport();
		GetHUD<AXYZHUD>()->BoxEnd = BoxSelectEnd;
	}
	
	// if still below short press threshold do not do anything with this input
	if (InputTriggeredTime[InputType] <= ShortInputThreshold) {
		return;
	}

	if (!bCanInputRepeatWhileTriggered && InputType != EXYZInputType::PRIMARY_INPUT) return;
	bCanInputRepeatWhileTriggered = false;
	GetWorld()->GetTimerManager().SetTimer(InputTriggeredCooldownTimer, [this]() {
		bCanInputRepeatWhileTriggered = true;
		}, InputTriggeredCooldown, false);

	FXYZInputMessage InputStopMessage(0, SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, true);

	switch (InputType) {
	case EXYZInputType::PRIMARY_INPUT:
		OnSelectionBoxTriggered.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		break;
	case EXYZInputType::SECONDARY_INPUT:
		// If we dont hit an actor send a move input
		if (bWorldHitSuccessful && !SelectionStructure->IsEmpty())
		{
			FXYZInputMessage InputMessage(0, SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, bPrimaryModifier);
			QueueInput(InputMessage);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
		break;
	}
	return;
}

void AXYZPlayerController::OnInputReleased(EXYZInputType InputType)
{
	//LONG INPUT RELEASE
	FHitResult BoxHitStart, BoxHitEnd;
	switch (InputType) {
	case EXYZInputType::PRIMARY_MOD:
		bPrimaryModifier = false;
		break;
	case EXYZInputType::SECONDARY_MOD:
		bSecondaryModifier = false;
		break;
	case EXYZInputType::PRIMARY_INPUT:
		OnSelectionBoxReleased.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		SelectActors(GetHUD<AXYZHUD>()->SelectedActors);
		GetHUD<AXYZHUD>()->bSelectActors = false;
		break;
	case EXYZInputType::SECONDARY_INPUT:
		if (bWorldHitSuccessful && !SelectionStructure->IsEmpty())
		{
			FXYZInputMessage InputMessage(0, SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, bPrimaryModifier);
			QueueInput(InputMessage);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
		break;
	}
}

void AXYZPlayerController::SelectActors(TArray<AXYZActor*> XYZActors){

	if (XYZActors.IsEmpty()) {
		SelectionStructure->Empty();
		FString SelectedActorsString = SelectionStructure->ToString();
		UE_LOG(LogTemp, Warning, TEXT("Selected Actors: %s"), *SelectedActorsString);
		return;
	}

	if (XYZActors.Num() == 1 && SelectionStructure->Contains(XYZActors[0]) && bPrimaryModifier) {
		SelectionStructure->Remove(XYZActors[0]);
		FString SelectedActorsString = SelectionStructure->ToString();
		UE_LOG(LogTemp, Warning, TEXT("Selected Actors: %s"), *SelectedActorsString);
		return;
	}

	if (bPrimaryModifier) {
		bool bInSelection = true;
		for (AXYZActor* XYZActor : XYZActors) {
			bInSelection = bInSelection && SelectionStructure->Contains(XYZActor);
		}
		if (bInSelection && XYZActors.Num() != SelectionStructure->ToArray().Num()) {
			SelectionStructure->Remove(XYZActors);
			FString SelectedActorsString = SelectionStructure->ToString();
			UE_LOG(LogTemp, Warning, TEXT("Selected Actors: %s"), *SelectedActorsString);
		}
		else {
			SelectionStructure->Add(XYZActors);
		}
		return;
	} 
	else {
		SelectionStructure->Empty();
		SelectionStructure->Add(XYZActors);
	}
}

FVector2D AXYZPlayerController::GetMousePositionOnViewport()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0); // Change 0 to the appropriate player index
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

void AXYZPlayerController::QueueInput_Implementation(const FXYZInputMessage& InputMessage) {
	if (GetLocalRole() != ROLE_Authority) return;
	AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();
	if (GameMode) {
		GameMode->QueueInput(InputMessage);
	}
}