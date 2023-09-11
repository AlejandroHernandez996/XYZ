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
#include "GameFramework/PlayerState.h"
#include "EnhancedInputSubsystems.h"
#include "UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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

	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	if (bAttackModifier || !SelectionStructure->IsEmpty() && HitActor && HitActor->TeamId != TeamId) {
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
	else{
		CurrentMouseCursor = EMouseCursor::Default;
	}

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

		EnhancedInputComponent->BindAction(ClearSelectionInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::CLEAR);

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
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
	}
}

void AXYZPlayerController::OnInputStarted(EXYZInputType InputType)
{
	InputTriggeredTime[InputType] = 0.0f;
	FXYZInputMessage InputMessage;
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
	switch (InputType) {
		case EXYZInputType::PRIMARY_INPUT:
			if (!bAllowMouseInput) return;
			if (bAttackModifier) {
				if (SelectionStructure->IsEmpty()) return;
				bAttackModifier = false;
				bBlockPrimaryInputFlagForAttack = true;
				CreateAndQueueInput(SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, EXYZInputType::ATTACK_MOVE, bPrimaryModifier);
				if (!HitActor || (SelectionStructure->Num == 1 && SelectionStructure->ToActorIdArray()[0] == XYZActorHitId)) {
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, AttackCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
				}
				break;
			}
			BoxSelectStart = GetMousePositionOnViewport();
			GetHUD<AXYZHUD>()->bSelectActors = true;
			GetHUD<AXYZHUD>()->BoxStart = BoxSelectStart;
			GetHUD<AXYZHUD>()->BoxEnd = BoxSelectStart;
			// Fire the SelectionBox event
			OnSelectionBox.Broadcast(BoxSelectStart.X, BoxSelectStart.Y);
			bBoxSelectFlag = true;
			break;
		case EXYZInputType::SECONDARY_INPUT:
			if (!bAllowMouseInput) return;
			bAttackModifier = false;
			if (SelectionStructure->IsEmpty()) return;
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, InputType, bPrimaryModifier);
			if (!HitActor || (SelectionStructure->Num == 1 && SelectionStructure->ToActorIdArray()[0] == XYZActorHitId)) {
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MoveCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}
			break;
		case EXYZInputType::PRIMARY_MOD:
			bPrimaryModifier = true;
			break;
		case EXYZInputType::SECONDARY_MOD:
			bSecondaryModifier = true;
			break;
		case EXYZInputType::ATTACK_MOVE:
			if (!SelectionStructure->IsEmpty()) {
				bAttackModifier = true;
			}
			break;
		case EXYZInputType::STOP:
			bAttackModifier = false;
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, false);
			break;
		case EXYZInputType::CLEAR:
			SelectActors({});
			OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
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

	switch (InputType) {
	case EXYZInputType::PRIMARY_INPUT:
		if (!bAllowMouseInput) return;
		if (!bBoxSelectFlag || !bAllowMouseInput) return;
		OnSelectionBoxTriggered.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		break;
	case EXYZInputType::ATTACK_MOVE:
		bAttackModifier = !SelectionStructure->IsEmpty();
		break;
	}
	return;
}

void AXYZPlayerController::OnInputReleased(EXYZInputType InputType)
{
	//LONG INPUT RELEASE
	FHitResult BoxHitStart, BoxHitEnd;
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;

	switch (InputType) {
	case EXYZInputType::PRIMARY_MOD:
		bPrimaryModifier = false;
		break;
	case EXYZInputType::SECONDARY_MOD:
		bSecondaryModifier = false;
		break;
	case EXYZInputType::PRIMARY_INPUT:
		if (!bAllowMouseInput) return;
		if (!bBoxSelectFlag) break;
		bBoxSelectFlag = false;
		OnSelectionBoxReleased.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		SelectActors(GetHUD<AXYZHUD>()->SelectedActors);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
		GetHUD<AXYZHUD>()->bSelectActors = false;
		break;
	case EXYZInputType::ATTACK_MOVE:
		break;
	}
}

void AXYZPlayerController::SelectActors(TArray<AXYZActor*> _XYZActors){
	TSet<AXYZActor*> XYZActorsSet = TSet<AXYZActor*>(_XYZActors);
	TArray<AXYZActor*> XYZActors = XYZActorsSet.Array();

	if (XYZActors.IsEmpty()) {
		SelectionStructure->Empty();
		return;
	}

	if (XYZActors.Num() == 1 && XYZActors[0]->TeamId != TeamId) {
		SelectionStructure->SelectEnemyActor(XYZActors[0]);
		return;
	}

	TArray<AXYZActor*> OwnedXYZActors;
	for (auto XYZActor : XYZActors) {
		if (XYZActor->TeamId == TeamId) {
			OwnedXYZActors.Add(XYZActor);
		}
	}

	if (OwnedXYZActors.Num() == 1 && SelectionStructure->Contains(OwnedXYZActors[0]) && bPrimaryModifier) {
		SelectionStructure->Remove(OwnedXYZActors[0]);
		return;
	}

	if (bPrimaryModifier) {
		bool bInSelection = true;
		for (AXYZActor* XYZActor : OwnedXYZActors) {
			bInSelection = bInSelection && SelectionStructure->Contains(XYZActor);
		}
		if (bInSelection && OwnedXYZActors.Num() != SelectionStructure->ToArray().Num()) {
			SelectionStructure->Remove(OwnedXYZActors);
		}
		else {
			SelectionStructure->Add(OwnedXYZActors);
		}
		return;
	} 
	else {
		SelectionStructure->Empty();
		SelectionStructure->Add(OwnedXYZActors);
	}
}

FVector2D AXYZPlayerController::GetMousePositionOnViewport()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0); // Change 0 to the appropriate player index
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

void AXYZPlayerController::CreateAndQueueInput(TArray<int32> _SelectedActors, int32 _XYZTargetActor, FVector _TargetLocation, EXYZInputType _InputType, bool _bQueueInput) {
	QueueInput(FXYZInputMessage(PlayerState->GetUniqueId().ToString(), _SelectedActors, _XYZTargetActor, _TargetLocation, _InputType, _bQueueInput));
}
void AXYZPlayerController::QueueInput_Implementation(const FXYZInputMessage& InputMessage) {
	if (GetLocalRole() != ROLE_Authority) return;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AXYZPlayerController* XYZController = Cast<AXYZPlayerController>(Iterator->Get());
		if (!XYZController) return;

		FString Id = Iterator->Get()->GetPlayerState<APlayerState>()->GetUniqueId().ToString();
		if (Id == InputMessage.PlayerId)
		{
			AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();
			if (GameMode) {
				TMap<int32, AXYZActor*> ActorsByUId = GameMode->GetGameState<AXYZGameState>()->ActorsByUID;
				for (int32 UActorId : InputMessage.SelectedActors) {
					if (!ActorsByUId.Contains(UActorId)) {
						return;
					}
					UE_LOG(LogTemp, Warning, TEXT("ActorsByUId[UActorId]->TeamId: %d, XYZController->TeamId: %d"), ActorsByUId[UActorId]->TeamId, XYZController->TeamId);
					if (ActorsByUId[UActorId]->TeamId != XYZController->TeamId) {
						return;
					}
				}
				GameMode->QueueInput(InputMessage);
			}
			break;
		}
	}
}

void AXYZPlayerController::SelectActorFromPanel(int32 UActorId) {
	if (GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Contains(UActorId)) {
		SelectActors({ GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID[UActorId]});
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
	}
}

bool AXYZPlayerController::IsMouseOverWidget()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UUserWidget::StaticClass(), false);
	bool bWidgetIsHovered = false;
	for (UUserWidget* Widget : FoundWidgets)
	{
		if (Widget->GetName().Contains("Healthbar"))
			continue;

		if (Widget->IsHovered()) {
			bWidgetIsHovered = true;
			return true;
		}
			
	}
	return bWidgetIsHovered;
}

void AXYZPlayerController::XYZActorDestroyed_Implementation(int32 ActorUId) {
	GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Remove(ActorUId);

	if (GetLocalRole() != ROLE_Authority) {
		if (SelectionStructure->Contains(ActorUId)) {
			SelectionStructure->Remove(ActorUId);
		}
		SelectionStructure->RemoveFromControlGroups(ActorUId);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
	}
}
