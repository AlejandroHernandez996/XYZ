// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "EngineUtils.h"
#include "XYZInputManager.h"
#include "XYZGameState.h"
#include "XYZBlobManager.h"
#include "LoginHandler.h"
#include "UserInfoRetriver.h"
#include "UserStatRetriever.h"
#include "UserStatUpdater.h"
#include "SessionHandler.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
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

    // Create an instance of the LoginHandler
    bUseSeamlessTravel = true;

    // Call the Login function
    SessionHandler = NewObject<USessionHandler>(this);
    LoginHandler = NewObject<ULoginHandler>(this);
    UserRetriever = NewObject<UUserInfoRetriver>(this);
    UserStatRetriever = NewObject<UUserStatRetriever>(this);
    UserStatUpdater = NewObject<UUserStatUpdater>(this);

    bAllExistingPlayersRegistered = false;
    if (HasAuthority()) {
        SessionHandler->CreateSession();
    }
    bIsCreatingSession = true;
}

void AXYZGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if (SessionHandler && !bIsCreatingSession && SessionHandler->bHasCreatedSession && NumOfPlayers >= 2) {
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
        bIsCreatingSession = true;
        Session->StartSession("MyLocalSessionName");
    }

    if (NumOfPlayers >= 2 && !bRetrivedUsersInfo) {
        TArray<TSharedRef<const FUniqueNetId>> UniqueNetIds;
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            // Get the UniqueNetId for each player
            TSharedRef<const FUniqueNetId> UniqueNetId = It->Get()->PlayerState->UniqueId.GetUniqueNetId().ToSharedRef();
            UniqueNetIds.Add(UniqueNetId);
        }
        UserRetriever->GetAllUserNetIdsToDisplayNames(UniqueNetIds);
        bRetrivedUsersInfo = UserRetriever->bRetrievedAllUsers;
    }
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

void AXYZGameMode::QueueInput(const FXYZInputMessage& InputMessage) {
    if (GetLocalRole() != ROLE_Authority) return;
    int32 TickCountCopy = TickCount;
    FXYZInputMessage TickInput = FXYZInputMessage(InputMessage, TickCountCopy);
    TickInput.AbilityIndex = InputMessage.AbilityIndex;
    TickInput.ActiveActorId = InputMessage.ActiveActorId;
    InputManager->QueueInput(TickInput);
    bHandleInputQueue = true;
}


void AXYZGameMode::RegisterExistingPlayers()
{
    for (auto It = this->GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = It->Get();

        FUniqueNetIdRepl UniqueNetIdRepl;
        if (PlayerController->IsLocalPlayerController())
        {
            ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
            if (IsValid(LocalPlayer))
            {
                UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
            }
            else
            {
                UNetConnection* RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
                check(IsValid(RemoteNetConnection));
                UniqueNetIdRepl = RemoteNetConnection->PlayerId;
            }
        }
        else
        {
            UNetConnection* RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
            check(IsValid(RemoteNetConnection));
            UniqueNetIdRepl = RemoteNetConnection->PlayerId;
        }

        // Get the unique player ID.
        TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
        check(UniqueNetId != nullptr);

        // Get the online session interface.
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(PlayerController->GetWorld());
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

        // Register the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
        if (!Session->RegisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId, false))
        {
            // The player could not be registered; typically you will want to kick the player from the server in this situation.
        }
    }

    bAllExistingPlayersRegistered = true;
}

void AXYZGameMode::PostLogin(APlayerController* InPlayerController)
{
    if (!bAllExistingPlayersRegistered)
    {
        // RegisterExistingPlayers has not run yet. When it does, it will register this incoming player
        // controller.
        Super::PostLogin(InPlayerController);
        return;
    }

    check(IsValid(InPlayerController));

    // This code handles logins for both the local player (listen server) and remote players (net connection).
    FUniqueNetIdRepl UniqueNetIdRepl;
    if (InPlayerController->IsLocalPlayerController())
    {
        ULocalPlayer* LocalPlayer = InPlayerController->GetLocalPlayer();
        if (IsValid(LocalPlayer))
        {
            UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
        }
        else
        {
            UNetConnection* RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
            check(IsValid(RemoteNetConnection));
            UniqueNetIdRepl = RemoteNetConnection->PlayerId;
        }
    }
    else
    {
        UNetConnection* RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
        check(IsValid(RemoteNetConnection));
        UniqueNetIdRepl = RemoteNetConnection->PlayerId;
    }

    // Get the unique player ID.
    TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
    check(UniqueNetId != nullptr);

    // Get the online session interface.
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(InPlayerController->GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Register the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
    if (!Session->RegisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId, false))
    {
        // The player could not be registered; typically you will want to kick the player from the server in this situation.
    }

    Super::PostLogin(InPlayerController);
    NumOfPlayers++;
    UserRetriever->SetUserNetIdsToDisplayName(InPlayerController);
}

void AXYZGameMode::PreLogout(APlayerController* InPlayerController)
{
    check(IsValid(InPlayerController));

    // This code handles logins for both the local player (listen server) and remote players (net connection).
    FUniqueNetIdRepl UniqueNetIdRepl;
    if (InPlayerController->IsLocalPlayerController())
    {
        ULocalPlayer* LocalPlayer = InPlayerController->GetLocalPlayer();
        if (IsValid(LocalPlayer))
        {
            UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
        }
        else
        {
            UNetConnection* RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
            check(IsValid(RemoteNetConnection));
            UniqueNetIdRepl = RemoteNetConnection->PlayerId;
        }
    }
    else
    {
        UNetConnection* RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
        check(IsValid(RemoteNetConnection));
        UniqueNetIdRepl = RemoteNetConnection->PlayerId;
    }

    // Get the unique player ID.
    TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
    check(UniqueNetId != nullptr);

    // Get the online session interface.
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(InPlayerController->GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Unregister the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
    if (!Session->UnregisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId))
    {
        // The player could not be unregistered.
    }
}