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
#include "Kismet/GameplayStatics.h" // Include this header
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
	}
}

void AXYZPlayerController::OnInputStarted(EXYZInputType InputType)
{
	InputTriggeredTime[InputType] = 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("Input Started for Type %d"), static_cast<int32>(InputType));
	switch (InputType) {
		case EXYZInputType::PRIMARY_INPUT:
			BoxSelectStart = GetMousePositionOnViewport();
			break;
		case EXYZInputType::PRIMARY_MOD:
			bPrimaryModifier = true;
			break;
		case EXYZInputType::SECONDARY_MOD:
			bSecondaryModifier = true;
			break;
	}
}

// Triggered every frame when the input is held down
void AXYZPlayerController::OnInputTriggered(EXYZInputType InputType)
{
	InputTriggeredTime[InputType] += GetWorld()->GetDeltaSeconds();

	// if still below short press threshold do not do anything with this input
	if (InputTriggeredTime[InputType] <= ShortInputThreshold) {
		return;
	}

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);

	FHitResult BoxHitStart, BoxHitEnd;
	bool bBoxHitStartSuccess = GetHitResultAtScreenPosition(BoxSelectStart, ECollisionChannel::ECC_WorldStatic, true, BoxHitStart);
	bool bBoxHitEndSuccess = GetHitResultAtScreenPosition(BoxSelectEnd, ECollisionChannel::ECC_WorldStatic, true, BoxHitEnd);
	FVector BoxCenter = (BoxHitStart.Location + BoxHitEnd.Location) / 2.0f; // Calculate the center.

	FVector BoxExtent = (BoxHitEnd.Location - BoxHitStart.Location) / 2.0f;

	float BoxHeight = 10.0f;

	FVector BoxMin = BoxCenter - FVector(BoxExtent.X, BoxExtent.Y, BoxHeight / 2.0f);
	FVector BoxMax = BoxCenter + FVector(BoxExtent.X, BoxExtent.Y, BoxHeight / 2.0f);

	FBox SelectionBox(BoxMin, BoxMax);
	switch (InputType) {
	case EXYZInputType::PRIMARY_INPUT:
		BoxSelectEnd = GetMousePositionOnViewport();
		
		DrawDebugBox(GetWorld(), SelectionBox.GetCenter(), SelectionBox.GetExtent(), FColor::Red, false, .1f, 0, 5);
		//UE_LOG(LogTemp, Warning, TEXT("Box Selection Start: %s"), *BoxSelectStart.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Box Selection End: %s"), *BoxSelectEnd.ToString());
		break;
	case EXYZInputType::SECONDARY_INPUT:
		// If we dont hit an actor send a move input
		if (bHitSuccessful && !Hit.GetActor())
		{
			// spawn some particles
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Hit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
		break;
	}
	return;
}

void AXYZPlayerController::OnInputReleased(EXYZInputType InputType)
{
	// if we are in short input threshold execute short input 
	FHitResult PawnHit;
	bool bPawnHitSuccessful = false;

	bPawnHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, PawnHit);

	FHitResult WorldHit;
	bool bWorldHitSuccessful = false;

	bWorldHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, WorldHit);

	if (InputTriggeredTime[InputType] <= ShortInputThreshold) {
		switch (InputType) {
		case EXYZInputType::PRIMARY_INPUT:
			// If we dont hit an actor send a move input
			if (bPawnHitSuccessful && PawnHit.GetActor())
			{
				AXYZActor* SelectedActor = Cast<AXYZActor>(PawnHit.GetActor());
				if (SelectedActor) {
					SelectActors({ SelectedActor });
				}
			}
			break;
		case EXYZInputType::SECONDARY_INPUT:
			// If we dont hit an actor send a move input
			if (bWorldHitSuccessful && !SelectedActors.IsEmpty())
			{
				TArray<int32> SelectedActorIds;
				TArray<TArray<AXYZActor*>> ActorArrays;
				SelectedActors.GenerateValueArray(ActorArrays);
				for (auto arr : ActorArrays) {
					for (auto a : arr) {
						SelectedActorIds.Add(a->UActorId);
					}
				}
				FXYZInputMessage InputMessage(0, SelectedActorIds, -1, WorldHit.Location, InputType, bPrimaryModifier);
				QueueInput(InputMessage);
				FString messageString = InputMessage.ToString();
				UE_LOG(LogTemp, Warning, TEXT("Queued Input: %s"), *messageString);
				// spawn some particles
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}
			break;
		case EXYZInputType::PRIMARY_MOD:
			bPrimaryModifier = false;
			break;
		case EXYZInputType::SECONDARY_MOD:
			bSecondaryModifier = false;
			break;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Input Triggered for Type %d (Short Press) - Time Triggered: %f seconds"),static_cast<int32>(InputType), InputTriggeredTime[InputType]);
		return;
	}
	FHitResult BoxHitStart, BoxHitEnd;
	bool bBoxHitStartSuccess = GetHitResultAtScreenPosition(BoxSelectStart, ECollisionChannel::ECC_WorldStatic, true, BoxHitStart);
	bool bBoxHitEndSuccess = GetHitResultAtScreenPosition(BoxSelectEnd, ECollisionChannel::ECC_WorldStatic, true, BoxHitEnd);
	switch (InputType) {
	case EXYZInputType::PRIMARY_MOD:
		bPrimaryModifier = false;
		break;
	case EXYZInputType::SECONDARY_MOD:
		bSecondaryModifier = false;
		break;
	case EXYZInputType::PRIMARY_INPUT:
		
		if (!(bBoxHitEndSuccess && bBoxHitStartSuccess)) return;

		FVector BoxCenter = (BoxHitStart.Location + BoxHitEnd.Location) / 2.0f; // Calculate the center.
		FVector BoxExtent = (BoxHitEnd.Location - BoxHitStart.Location) / 2.0f;
		float BoxHeight = 10.0f;
		FVector BoxMin = BoxCenter - FVector(BoxExtent.X, BoxExtent.Y, BoxHeight / 2.0f);
		FVector BoxMax = BoxCenter + FVector(BoxExtent.X, BoxExtent.Y, BoxHeight / 2.0f);

		FBox SelectionBox(BoxMin, BoxMax); 

		TArray<AXYZActor*> XYZActors;
		// Populate OverlapResults with actors that are in the box
		DrawDebugBox(GetWorld(), SelectionBox.GetCenter(), SelectionBox.GetExtent(), FColor::Green, false, 3.0f, 0, 5);
		AXYZGameState* MyGameState = Cast<AXYZGameState>(GetWorld()->GetGameState());
		UE_LOG(LogTemp, Warning, TEXT("Box Min: %s, Max: %s"), *SelectionBox.Min.ToString(), *SelectionBox.Max.ToString());
		for (AXYZActor* XYZActor : MyGameState->AllActors)
		{
			FVector ActorLocation = XYZActor->GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("Actor %s is at %s"), *XYZActor->GetName(), *ActorLocation.ToString());
			// Since height doesn't matter, we only check the X and Y coordinates
			if (ActorLocation.X >= FMath::Min(SelectionBox.Max.X, SelectionBox.Min.X) && ActorLocation.X <= FMath::Max(SelectionBox.Max.X, SelectionBox.Min.X) &&
				ActorLocation.Y >= FMath::Min(SelectionBox.Max.Y, SelectionBox.Min.Y) && ActorLocation.Y <= FMath::Max(SelectionBox.Max.Y, SelectionBox.Min.Y))
			{
				// Actor is inside the box, add to array
				XYZActors.Add(XYZActor);
			}
		}
		
		// Debug draw the selection box.

		if (XYZActors.Num() > 0) {
			SelectActors(XYZActors);
		}
		BoxSelectStart = FVector2D::ZeroVector;
		BoxSelectEnd = FVector2D::ZeroVector;
		break;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Input Triggered for Type %d (Long Press) - Time Triggered: %f seconds"), static_cast<int32>(InputType), InputTriggeredTime[InputType]);
}

void AXYZPlayerController::SelectActors(TArray<AXYZActor*> XYZActors){
	SelectedActors.Empty();
	for (AXYZActor* XYZActor : XYZActors) {
		AddActorToSelection(XYZActor);
	}
}

void AXYZPlayerController::AddActorToSelection(AXYZActor* XYZActor)
{
	if (!XYZActor) return;
	int32 ActorId = XYZActor->ActorId;
	if (SelectedActors.Contains(ActorId))
	{
		SelectedActors[ActorId].Add(XYZActor);
	}
	else
	{
		SelectedActors.Add(ActorId, { XYZActor });
	}
	// Log the addition of the actor
	UE_LOG(LogTemp, Warning, TEXT("Added actor with ID %d to selection. UID %d"), ActorId, XYZActor->UActorId);
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