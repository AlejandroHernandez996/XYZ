// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYZPlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "DrawDebugHelpers.h"
#include "XYZSelectionStructure.h"
#include "Kismet/GameplayStatics.h" 
#include "XYZHUD.h"
#include "GameFramework/PlayerState.h"
#include "EnhancedInputSubsystems.h"
#include "XYZCameraController.h"
#include "XYZResourceActor.h"
#include "EngineUtils.h"
#include "XYZBuilding.h"
#include "XYZFogOfWar.h"
#include "Net/UnrealNetwork.h"

AXYZPlayerController::AXYZPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
		EnumValue <= static_cast<int32>(EXYZInputType::STOP);
		EnumValue++)
	{
		InputTriggeredTime.Add(static_cast<EXYZInputType>(EnumValue), 0.0f);
	}
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
		EnumValue <= static_cast<int32>(EXYZInputType::STOP);
		EnumValue++)
	{
		LastInputTime.Add(static_cast<EXYZInputType>(EnumValue), 0.0f);
	}
	ShortInputThreshold = .25f;
	PrimaryActorTick.bCanEverTick = true;
}

void AXYZPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SelectionStructure = NewObject<UXYZSelectionStructure>(this, UXYZSelectionStructure::StaticClass(), "SelectionStructure");
	SelectionStructure->InitControlGroups(ControlGroupInputActions.Num());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	for (TActorIterator<AXYZCameraController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		CameraController = *ActorItr;
	}

}

void AXYZPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (GetLocalRole() != ROLE_Authority || GetWorld()->GetGameState<AXYZGameState>() && !bPingedGameLoaded) {
		bPingedGameLoaded = true;
		PingServerGameIsLoaded();
	}
	UpdateVisibleActors();
	UpdateMouseCursor();
	
	float x, y;
	if (!GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y)) {
		OnSelectionBoxReleased.Broadcast(0, 0);
	}

	bWorldHitSuccessful = GetHitResultAtScreenPosition(GetMousePositionOnViewport(), ECollisionChannel::ECC_WorldStatic, true, WorldHit);
	bXYZActorHitSuccessful = GetHitResultAtScreenPosition(GetMousePositionOnViewport(), ECollisionChannel::ECC_WorldStatic, true, XYZActorHit);

	if(CameraController && bMoveCameraFlag && !HasAuthority())
	{
		FVector LocationWithOffset = FVector(CameraLocation.X, CameraLocation.Y, CameraController->GetActorLocation().Z) + FVector(-250, 50,0.0f);
		CameraController->SetActorLocation(LocationWithOffset);
		bMoveCameraFlag = false;
	}
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
			EnumValue <= static_cast<int32>(EXYZInputType::STOP);
			EnumValue++)
	{
		InputTriggeredTime[static_cast<EXYZInputType>(EnumValue)] += DeltaTime;
	}
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
			EnumValue <= static_cast<int32>(EXYZInputType::STOP);
			EnumValue++)
	{
		LastInputTime[static_cast<EXYZInputType>(EnumValue)] += DeltaTime;
	}
	for(int32 i = 0;i < LastControlGroupInputTime.Num();i++)
	{
		LastControlGroupInputTime[i] += DeltaTime;
	}
	if(!FogOfWar)
	{
		for (TActorIterator<AXYZFogOfWar> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			FogOfWar = *ActorItr;
		}
	}
}

void AXYZPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
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
		EnhancedInputComponent->BindAction(CycleSelectionInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnCycleSelectionInputStarted);

		for (int32 i = 0; i < ControlGroupInputActions.Num(); i++) {
			EnhancedInputComponent->BindAction(ControlGroupInputActions[i], ETriggerEvent::Started, this, &AXYZPlayerController::OnControlGroupInputStarted, i);
			LastControlGroupInputTime.Add(i,0.0f);
		}
		for (int32 i = 0; i < AbilityInputActions.Num(); i++) {
			EnhancedInputComponent->BindAction(AbilityInputActions[i], ETriggerEvent::Started, this, &AXYZPlayerController::OnAbilityInputStarted, i);
		}
	}
}

void AXYZPlayerController::OnControlGroupInputStarted(int32 ControlGroupIndex) {
	bool bDoubleInput = LastControlGroupInputTime[ControlGroupIndex] <= DoubleInputThreshold;
	LastControlGroupInputTime[ControlGroupIndex] = 0.0f;
	if (bPrimaryModifier) {
		SelectionStructure->AddToControlGroup(ControlGroupIndex);
	}
	else if (bSecondaryModifier) {
		SelectionStructure->SetControlGroup(ControlGroupIndex);
	}
	else {
		SelectionStructure->SelectControlGroup(ControlGroupIndex);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
		if(bDoubleInput && !SelectionStructure->IsEmpty())
		{
			FVector TargetActorLocation = SelectionStructure->ToArray()[0]->GetActorLocation();
			CameraController->SetActorLocation(FVector(TargetActorLocation.X, TargetActorLocation.Y, CameraController->GetActorLocation().Z) + FVector(-250.0f, 50.0f, 0.0f));
		}
	}
	TArray<int32> ControlGroups;
	for (TSortedMap<int32, TMap<int32, AXYZActor*>> ControlGroup : SelectionStructure->ControlGroups) {
		ControlGroups.Add(ControlGroup.Num());
	}
	OnControlGroupEvent.Broadcast(ControlGroups);
}

void AXYZPlayerController::OnAbilityInputStarted(int32 AbilityIndex) {
	if (SelectionStructure->IsEmpty()) return;

	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
	FXYZInputMessage AbilityInput = FXYZInputMessage(PlayerState->GetUniqueId().ToString(), SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, EXYZInputType::ABILITY, bPrimaryModifier);
	AbilityInput.AbilityIndex = AbilityIndex;
	AbilityInput.ActiveActorId = SelectionStructure->ActiveActor;
	QueueInput(AbilityInput);
}

void AXYZPlayerController::OnCycleSelectionInputStarted() {
	SelectionStructure->CycleSelection();
}

void AXYZPlayerController::OnInputStarted(EXYZInputType InputType)
{
	FXYZInputMessage InputMessage;
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
	switch (InputType) {
		case EXYZInputType::PRIMARY_INPUT:
			UE_LOG(LogTemp, Warning, TEXT("Primary Input Pressed"));
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

void AXYZPlayerController::OnInputTriggered(EXYZInputType InputType)
{
	if (InputType == EXYZInputType::PRIMARY_INPUT) {
		BoxSelectEnd = GetMousePositionOnViewport();
		GetHUD<AXYZHUD>()->BoxEnd = BoxSelectEnd;
	}
	
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
		OnSelectionBoxTriggered.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		break;
	case EXYZInputType::ATTACK_MOVE:
		bAttackModifier = !SelectionStructure->IsEmpty();
		break;
	}
}

void AXYZPlayerController::OnInputReleased(EXYZInputType InputType)
{
	FHitResult BoxHitStart, BoxHitEnd;
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
	InputTriggeredTime[InputType] = 0.0f;
	bool bDoubleInput = LastInputTime[InputType] <= DoubleInputThreshold;
	LastInputTime[InputType] = 0.0f;
	switch (InputType) {
	case EXYZInputType::PRIMARY_MOD:
		UE_LOG(LogTemp, Warning, TEXT("Primary Mod Released"));
		bPrimaryModifier = false;
		break;
	case EXYZInputType::SECONDARY_MOD:
		bSecondaryModifier = false;
		break;
	case EXYZInputType::PRIMARY_INPUT:
		UE_LOG(LogTemp, Warning, TEXT("Primary Input Released"));
		if(bBlockPrimaryInputFlagForAttack)
		{
			bBlockPrimaryInputFlagForAttack = false;
			break;
		}
		if (!bAllowMouseInput || !bBoxSelectFlag) break;
		if (FVector2D::Distance(BoxSelectStart, BoxSelectEnd) < 25.0f){
			if (HitActor) {
				if (bSecondaryModifier || bDoubleInput) {
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
				}else
				{
					SelectActors({ HitActor });
				}
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
		OnSelectionBoxTriggered.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
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
	XYZActors.RemoveAll([&](AXYZActor* Actor) {
		return Actor->Health <= 0.0f;
		});
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
	if(!GetWorld() || !GetWorld()->GetGameState<AXYZGameState>()) return;
	if (GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Contains(ActorUId)) {
		AXYZActor* Actor = GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID[ActorUId];
		if (!Actor) return;
		USkeletalMeshComponent* Ragdoll = Actor->GetMesh();
		Ragdoll->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		Ragdoll->SetCollisionProfileName("Ragdoll");
		Ragdoll->SetSimulatePhysics(true);
		FVector ForceDirection = FVector(0, 0, 6000);
		Ragdoll->AddForce(ForceDirection);
		Actor->ShowDecal(false, EXYZDecalType::NEUTRAL);
		if (SelectionStructure->Contains(ActorUId)) {
			SelectionStructure->Remove(ActorUId);
		}
		SelectionStructure->RemoveFromControlGroups(ActorUId, Actor->ActorId);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());

		TArray<int32> ControlGroups;
		for (TSortedMap<int32, TMap<int32, AXYZActor*>> ControlGroup : SelectionStructure->ControlGroups) {
			ControlGroups.Add(ControlGroup.Num());
		}
		OnControlGroupEvent.Broadcast(ControlGroups);
		GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Remove(ActorUId);

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
			{
				if (Cast<USkeletalMeshComponent>(SceneComponent))
				{
					continue;
				}
				SceneComponent->SetVisibility(false);
			}
		}

	}
	
}
void AXYZPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZPlayerController, TeamId);
}

void AXYZPlayerController::Disconnect_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "DISCONNECTED FROM MATCH");
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("MainMenuMap")));
}

void AXYZPlayerController::FocusCameraOnLocation_Implementation(FVector Location)
{
	if(HasAuthority()) return;
	bMoveCameraFlag = true;
	CameraLocation =Location; 
}

void AXYZPlayerController::PingServerGameIsLoaded_Implementation() {
	AXYZGameState* GameState = GetWorld()->GetGameState<AXYZGameState>();
	GameState->bClientLoaded = true;
}

AXYZActor* AXYZPlayerController::GetActiveSelectedActor() {
	AXYZActor* Result = nullptr;
	TArray<int32> ActiveActorIds = SelectionStructure->GetActiveActorIds();
	if (!ActiveActorIds.IsEmpty() && GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID.Contains(ActiveActorIds[0])) {
		Result = GetWorld()->GetGameState<AXYZGameState>()->ActorsByUID[ActiveActorIds[0]];
	}
	return Result;
}

void AXYZPlayerController::PlayAnimationMontage_Implementation(EXYZAnimMontageType AnimType, AXYZActor* Actor) {
	if (Actor->AnimMontageMap.Contains(AnimType)) {
		Actor->PlayAnimationMontage(AnimType);
	}
}

void AXYZPlayerController::OnNetCleanup(UNetConnection* Connection)
{
	if (GetLocalRole() == ROLE_Authority && PlayerState != NULL)
	{
		AXYZGameMode* GameMode = Cast<AXYZGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->PreLogout(this);
		}
	}

	Super::OnNetCleanup(Connection);
}

void AXYZPlayerController::UpdateMatchStatus_Implementation(int32 Status)
{
	MatchStatus = Status;
}

void AXYZPlayerController::SetVisibleEnemyActors_Implementation(const TArray<int32>& VisibleActors, const TArray<int32>& NonVisibleActors)
{
	NonVisibleEnemyActors = NonVisibleActors;
	VisibleEnemyActors = VisibleActors;
}

void AXYZPlayerController::SendVisibilityGridCoords_Implementation(const TArray<FVector2D>& DeltaVisible, const TArray<FVector2D>& DeltaNonVisible)
{
	if(FogOfWar)
	{
		FogOfWar->Update(DeltaVisible, DeltaNonVisible);
	}
	
}

void AXYZPlayerController::UpdateVisibleActors()
{
	if(GetLocalRole() != ROLE_Authority)
	{
		if(GetWorld())
		{
			AXYZGameState* XYZGameState = GetWorld()->GetGameState<AXYZGameState>();

			if(XYZGameState)
			{
				TArray<int32> ActorsNotFound;
				for(int32 VisibleActor : VisibleEnemyActors)
				{
					if(XYZGameState->ActorsByUID.Contains(VisibleActor))
					{
						XYZGameState->ActorsByUID[VisibleActor]->SetActorHiddenInGame(false);
					}else
					{
						ActorsNotFound.Add(VisibleActor);
					}
				}
				VisibleEnemyActors = ActorsNotFound;
				ActorsNotFound.Empty();
				for(int32 NonVisibleActor : NonVisibleEnemyActors)
				{
					if(XYZGameState->ActorsByUID.Contains(NonVisibleActor))
					{
						XYZGameState->ActorsByUID[NonVisibleActor]->SetActorHiddenInGame(true);
					}
					else
					{
						ActorsNotFound.Add(NonVisibleActor);
					}
				}
				NonVisibleEnemyActors = ActorsNotFound;
			}
		}
	}
}

void AXYZPlayerController::UpdateMouseCursor()
{
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	bool bHoveringEnemy = HitActor && HitActor->TeamId != TeamId;

	if (bAttackModifier && SelectionStructure && !SelectionStructure->IsEmpty()) {

		if (HitActor) {
			if (bHoveringEnemy && !HitActor->IsA(AXYZResourceActor::StaticClass())) {
				CurrentMouseCursor = EMouseCursor::Crosshairs;
			}
			else {
				CurrentMouseCursor = EMouseCursor::ResizeUpDown;
			}
		}
		else {
			CurrentMouseCursor = EMouseCursor::ResizeLeftRight;
		}
	}
	else {
		if (SelectionStructure && SelectionStructure->IsEmpty()) {
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
}
