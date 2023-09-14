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
	InputManager->QueueInput(TickInput);
	bHandleInputQueue = true;
}

void AXYZGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	BlobManager->ProcessBlobs();
	TickCount++;
}