// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYZGameMode.h"
#include "XYZPlayerController.h"
#include "EngineUtils.h"
#include "XYZInputManager.h"
#include "XYZGameState.h"
#include "XYZBlobManager.h"
#include "UserInfoRetriver.h"
#include "UserStatRetriever.h"
#include "UserStatUpdater.h"
#include "SessionHandler.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "XYZBaseBuilding.h"
#include "XYZDeathManager.h"
#include "XYZMatchManager.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "UObject/ConstructorHelpers.h"

AXYZGameMode::AXYZGameMode()
{
	PlayerControllerClass = AXYZPlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	TickCount = 0;
}

void AXYZGameMode::BeginPlay() {
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	InputManager = NewObject<UXYZInputManager>(this, UXYZInputManager::StaticClass(), "InputManager");
	BlobManager = NewObject<UXYZBlobManager>(this, UXYZBlobManager::StaticClass(), "BlobManager");
	InputManager->XYZGameState = GetWorld()->GetGameState<AXYZGameState>();
    DeathManager = NewObject<UXYZDeathManager>(this, UXYZDeathManager::StaticClass(), "DeathManager");
    MatchManager = NewObject<UXYZMatchManager>(this, UXYZMatchManager::StaticClass(), "MatchManager");
    MatchManager->XYZGameMode = this;
    MatchManager->XYZGameState = GetGameState<AXYZGameState>();

    SessionHandler = NewObject<USessionHandler>(this);
    UserRetriever = NewObject<UUserInfoRetriver>(this);
    UserStatRetriever = NewObject<UUserStatRetriever>(this);
    UserStatUpdater = NewObject<UUserStatUpdater>(this);

    bAllExistingPlayersRegistered = false;
	bUseSeamlessTravel = true;

	SessionHandler->CreateSession();
}

void AXYZGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if (SessionHandler && SessionHandler->bHasCreatedSession && NumOfPlayers == 2 && !bStartedSesion && bHasGameStarted) {
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
        Session->StartSession("MyLocalSessionName");
        bStartedSesion = true;
    }
    
    if (NumOfPlayers == 2 && !bRetrivedUsersInfo && !bHasGameStarted) {
        TArray<TSharedRef<const FUniqueNetId>> UniqueNetIds;
        int i = 0;
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            TSharedRef<const FUniqueNetId> UniqueNetId = It->Get()->PlayerState->UniqueId.GetUniqueNetId().ToSharedRef();
            Cast<AXYZPlayerController>(It->Get())->TeamId = i;
            PlayerControllers.Add(Cast<AXYZPlayerController>(It->Get()));
            UniqueNetIds.Add(UniqueNetId);
            i++;
        }
        if(UniqueNetIds.Num() == 2)
        {
            UserRetriever->GetAllUserNetIdsToDisplayNames(UniqueNetIds);
            bRetrivedUsersInfo = UserRetriever->bRetrievedAllUsers;
        }
    }
    if(bRetrivedUsersInfo && !bHasGameStarted)
    {
        TArray<AXYZPlayerController*> FoundControllers;
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            FoundControllers.Add(Cast<AXYZPlayerController>(It->Get()));
        }
        if(FoundControllers.Num() == 2)
        {
            for(int i = 0;i < FoundControllers.Num();i++)
            {
                FoundControllers[i]->TeamId = i;
                PlayerControllers.Add(FoundControllers[i]);
            }
            bHasGameStarted = true;
            GetGameState<AXYZGameState>()->LoadGameState();
            TArray<AXYZActor*> Actors;
            GetGameState<AXYZGameState>()->ActorsByUID.GenerateValueArray(Actors);

            for(AXYZActor* Actor : Actors)
            {
                if(Actor->IsA(AXYZBaseBuilding::StaticClass()))
                {
                    PlayerControllers[Actor->TeamId]->FocusCameraOnLocation(Actor->GetActorLocation());
                }
            }
        }
    }

    if(bHasGameStarted && !bHasGameEnded)
    {
        
        TArray<AXYZActor*> Actors;
        Cast<AXYZGameState>(GetWorld()->GetGameState())->ActorsByUID.GenerateValueArray(Actors);
        
        for(AXYZActor* Actor : Actors)
        {
            if(Actor)
            {
                Actor->Process(DeltaSeconds);
            }
        }
        InputManager->Process(DeltaSeconds);
        BlobManager->Process(DeltaSeconds);
        DeathManager->Process(DeltaSeconds);
        MatchManager->Process(DeltaSeconds);
        TickCount++;
        bHasGameEnded = bHasGameEnded || NumOfPlayers < 2;
        if (bHasGameEnded)
        {
            FTimerHandle TimerHandle;

            GetWorld()->GetTimerManager().SetTimer(
                TimerHandle,
                [this]() 
                {
                    SessionHandler->DestroySession();
                },
                3.0f, 
                false 
            );
        }
    }
	
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
    bHasGameEnded = true;
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