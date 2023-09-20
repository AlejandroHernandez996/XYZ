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
#include "XYZCameraController.h"
#include "XYZResourceActor.h"
#include "EngineUtils.h"
#include "XYZBuilding.h"

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
	ShortInputThreshold = .25f;
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
	if (GetLocalRole() != ROLE_Authority) {
		for (TActorIterator<AXYZCameraController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			CameraController = *ActorItr;
		}

	}
}

void AXYZPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	bool bHoveringEnemy = HitActor && HitActor->TeamId != TeamId;

	// Holding A and has a selection if not just default to regular cursor logic
	if (bAttackModifier && !SelectionStructure->IsEmpty()) {

		// Hovering an actor
		if (HitActor) {
			if (bHoveringEnemy && !HitActor->IsA(AXYZResourceActor::StaticClass())) {
				// Red Crosshair
				CurrentMouseCursor = EMouseCursor::Crosshairs;
			}
			else {
				// Yellow Crosshair
				CurrentMouseCursor = EMouseCursor::ResizeUpDown;
			}
		}
		else {
			// Green Crosshair
			CurrentMouseCursor = EMouseCursor::ResizeLeftRight;
		}
	}
	else {
		if (SelectionStructure->IsEmpty()) {
			if (HitActor && bHoveringEnemy) {
				CurrentMouseCursor = EMouseCursor::TextEditBeam;
			}
			else {
				CurrentMouseCursor = EMouseCursor::Default;
			}
		}
		else {
			if (HitActor) {
				if (bHoveringEnemy) {
					if (HitActor->IsA(AXYZResourceActor::StaticClass())) {
						CurrentMouseCursor = EMouseCursor::GrabHandClosed;
					}
					else {
						CurrentMouseCursor = EMouseCursor::GrabHand;
					}
				}
				else {
					CurrentMouseCursor = EMouseCursor::Hand;
				}
			}
			else {
				CurrentMouseCursor = EMouseCursor::Default;
			}
		}
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

		EnhancedInputComponent->BindAction(HoldInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::HOLD);

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
	TArray<int32> ControlGroups;
	for (TMap<int32, TMap<int32, AXYZActor*>> ControlGroup : SelectionStructure->ControlGroups) {
		ControlGroups.Add(ControlGroup.Num());
	}
	OnControlGroupEvent.Broadcast(ControlGroups);
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
			if (CameraController) {
				CameraController->bBlockMovementFlag = true;
			}
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
		case EXYZInputType::HOLD:
			bAttackModifier = false;
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, false);
			break;
		case EXYZInputType::CLEAR:
			SelectionStructure->Empty();
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
		if (!bAllowMouseInput || !bBoxSelectFlag) break;
		if (bSecondaryModifier && InputTriggeredTime[InputType] <= ShortInputThreshold) {
			TArray<AXYZActor*> SelectedActors = GetHUD<AXYZHUD>()->SelectedActors;
			SelectedActors.RemoveAll([&](AXYZActor* Actor)
				{
					if (Actor)
					{
						return Actor->TeamId != TeamId;
					}
					return true;
				});
			if (SelectedActors.Num() > 0) {
				AXYZActor* SelectedActor = SelectedActors[0];
				if (SelectedActor) {
					TArray<AXYZActor*> AllMatchingSelectedActorOnScreen = GetHUD<AXYZHUD>()->AllActorsOnScreen;
					AllMatchingSelectedActorOnScreen.RemoveAll([&](AXYZActor* Actor)
						{
							if (Actor)
							{
								return Actor->TeamId != TeamId || Actor->ActorId != SelectedActor->ActorId;
							}
							return true;
						});
					if (AllMatchingSelectedActorOnScreen.Num() > 0) {
						SelectActors(AllMatchingSelectedActorOnScreen);
					}
				}
			}
			GetHUD<AXYZHUD>()->AllActorsOnScreen.Empty();
		}
		else if (InputTriggeredTime[InputType] <= ShortInputThreshold && FVector2D::Distance(BoxSelectStart, BoxSelectEnd) < 10.0f){
			if (HitActor) {
				SelectActors({ HitActor });
			}
		}
		else {
			SelectActors(GetHUD<AXYZHUD>()->SelectedActors);
		}
		bBoxSelectFlag = false;
		GetHUD<AXYZHUD>()->bSelectActors = false;
		if (CameraController) {
			CameraController->bBlockMovementFlag = false;
		}
		OnSelectionBoxReleased.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
		break;
	case EXYZInputType::ATTACK_MOVE:
		break;
	}
}

void AXYZPlayerController::SelectActors(TArray<AXYZActor*> _XYZActors){
	TSet<AXYZActor*> XYZActorsSet = TSet<AXYZActor*>(_XYZActors);
	TArray<AXYZActor*> XYZActors = XYZActorsSet.Array();

	if (XYZActors.IsEmpty()) {
		return;
	}

	if (XYZActors.Num() == 1 && XYZActors[0]->IsA(AXYZResourceActor::StaticClass())) {
		SelectionStructure->SelectResource(XYZActors[0]);
		return;
	}

	if (XYZActors.Num() == 1 && XYZActors[0]->TeamId != TeamId) {
		SelectionStructure->SelectEnemyActor(XYZActors[0]);
		return;
	}
	XYZActors.RemoveAll([&](AXYZActor* Actor) {
		return Actor->IsA(AXYZResourceActor::StaticClass());
		});
	bool bSelectionOnlyBuildings = true;
	for (AXYZActor* Actor : XYZActors) {
		bSelectionOnlyBuildings = bSelectionOnlyBuildings && Actor->IsA(AXYZBuilding::StaticClass());
	}
	if (!bSelectionOnlyBuildings) {
		XYZActors.RemoveAll([&](AXYZActor* Actor) {
			return Actor->IsA(AXYZBuilding::StaticClass());
			});
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

void AXYZPlayerController::XYZActorDestroyed_Implementation(int32 ActorUId) {
	if (GetLocalRole() != ROLE_Authority) {
		if (GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Contains(ActorUId)) {
			AXYZActor* Actor = GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID[ActorUId];
			if (!Actor) return;
			Actor->GetMesh()->SetSimulatePhysics(true);
			Actor->GetMesh()->SetCollisionProfileName("Ragdoll");
			FVector ForceDirection = FVector(0, 0, 3000);  // Replace with your force direction
			Actor->GetMesh()->AddForce(ForceDirection);
			Actor->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			if (SelectionStructure->Contains(ActorUId)) {
				SelectionStructure->Remove(ActorUId);
			}
			SelectionStructure->RemoveFromControlGroups(ActorUId);
			OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());

			TArray<int32> ControlGroups;
			for (TMap<int32, TMap<int32, AXYZActor*>> ControlGroup : SelectionStructure->ControlGroups) {
				ControlGroups.Add(ControlGroup.Num());
			}
			OnControlGroupEvent.Broadcast(ControlGroups);
		}
	}
	GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Remove(ActorUId);
}
