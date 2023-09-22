// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "EngineUtils.h"
#include "XYZInputManager.h"
#include "XYZGameState.h"
#include "XYZBlobManager.h"
#include "UObject/ConstructorHelpers.h"

AXYZGameMode::AXYZGameMode()
{
	PlayerControllerClass = AXYZPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	TickCount = 0;
}

void AXYZGameMode::BeginPlay() {
	Super::BeginPlay();
	InputManager = NewObject<UXYZInputManager>(this, UXYZInputManager::StaticClass(), "InputManager");
	BlobManager = NewObject<UXYZBlobManager>(this, UXYZBlobManager::StaticClass(), "BlobManager");
	InputManager->XYZGameState = GetWorld()->GetGameState<AXYZGameState>();
	PrimaryActorTick.bCanEverTick = true;
}

void AXYZGameMode::QueueInput(const FXYZInputMessage& InputMessage) {
	if (GetLocalRole() != ROLE_Authority) return;
	int32 TickCountCopy = TickCount;
	FXYZInputMessage TickInput = FXYZInputMessage(InputMessage, TickCountCopy);
	TickInput.AbilityIndex = InputMessage.AbilityIndex;
	TickInput.ActiveActorId = InputMessage.ActiveActorId;
	InputManager->QueueInput(TickInput);
	bHandleInputQueue = true;
}

void AXYZGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TArray<AXYZPlayerController*> FoundControllers;
	// TODO - eventually make it only find a set amount and then stop looking
	for (auto It = GetWorld()->GetControllerIterator(); It; It++) {
		if (It->Get()) {
			if (Cast<AXYZPlayerController>(It->Get())) {
				FoundControllers.Add(Cast<AXYZPlayerController>(It->Get()));
			}
		}
	}
	if (FoundControllers.Num() > 0) {
		PlayerControllers = FoundControllers;
		for (int i = 0; i < PlayerControllers.Num(); i++) {
			PlayerControllers[i]->TeamId = i;
			
		}
	}
	BlobManager->ProcessBlobs();
	TickCount++;
}