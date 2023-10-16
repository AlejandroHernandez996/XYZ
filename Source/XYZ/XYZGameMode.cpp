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
#include "XYZActorCache.h"
#include "XYZBaseBuilding.h"
#include "XYZDeathManager.h"
#include "XYZMapManager.h"
#include "XYZMatchManager.h"
#include "XYZUpgradeManager.h"
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
    InputManager->XYZGameState = GetWorld()->GetGameState<AXYZGameState>();

    BlobManager = NewObject<UXYZBlobManager>(this, UXYZBlobManager::StaticClass(), "BlobManager");

    DeathManager = NewObject<UXYZDeathManager>(this, UXYZDeathManager::StaticClass(), "DeathManager");

    MatchManager = NewObject<UXYZMatchManager>(this, UXYZMatchManager::StaticClass(), "MatchManager");
    MatchManager->XYZGameMode = this;
    MatchManager->XYZGameState = GetGameState<AXYZGameState>();

    MapManager = NewObject<UXYZMapManager>(this, UXYZMapManager::StaticClass(), "MapManager");
    MapManager->GameState = GetGameState<AXYZGameState>();
    MapManager->GameMode = this;
    MapManager->InitializeGrid();
    
    UpgradeManager = NewObject<UXYZUpgradeManager>(this, UXYZUpgradeManager::StaticClass(), "UpgradeManager");
    UpgradeManager->GameState = GetGameState<AXYZGameState>();
        
    ActorCache = NewObject<UXYZActorCache>(this, UXYZActorCache::StaticClass(), "ActorCache");
    ActorCache->ActorCountsByTeamId.Add(FActorCount());
    ActorCache->ActorCountsByTeamId.Add(FActorCount());

    SessionHandler = NewObject<USessionHandler>(this);
    UserRetriever = NewObject<UUserInfoRetriver>(this);
    UserStatRetriever = NewObject<UUserStatRetriever>(this);
    UserStatUpdater = NewObject<UUserStatUpdater>(this);
    
    bAllExistingPlayersRegistered = false;
	bUseSeamlessTravel = true;

	SessionHandler->CreateSession();
    XYZGameState = GetGameState<AXYZGameState>();
}

void AXYZGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if(!XYZGameState)
    {
        XYZGameState = GetGameState<AXYZGameState>();
        return;
    }

    switch(XYZGameState->MatchState)
    {
    case EXYZMatchState::WAITING_FOR_PLAYERS:
        ProcessWaitingForPlayers();
        break;
    case EXYZMatchState::MATCH_STARTING:
        ProcessMatchStarting();
        TimeSinceStart += DeltaSeconds;
        break;
    case EXYZMatchState::IN_PROGRESS:
        Process(DeltaSeconds);
        TimeSinceStart += DeltaSeconds;
        XYZGameState->GameTime += DeltaSeconds;
        break;
    case EXYZMatchState::CLEANING_UP:
        ProcessCleanUp();
        break;
    case EXYZMatchState::SHUTTING_DOWN:
        ProcessShutdown();
        break;
    case EXYZMatchState::GAME_OVER:
        break;
    default: ;
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

void AXYZGameMode::ProcessWaitingForPlayers()
{
    if (SessionHandler && SessionHandler->bHasCreatedSession && NumOfPlayers == MAX_PLAYERS) {
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
        Session->StartSession("MyLocalSessionName");
        XYZGameState->ProgressMatchState();
    }
}

void AXYZGameMode::ProcessMatchStarting()
{
     if (!bRetrivedUsersInfo) {
        TArray<TSharedRef<const FUniqueNetId>> UniqueNetIds;
        TSet<AXYZPlayerController*> FoundControllers;
        int i = 0;
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            TSharedRef<const FUniqueNetId> UniqueNetId = It->Get()->PlayerState->UniqueId.GetUniqueNetId().ToSharedRef();
            Cast<AXYZPlayerController>(It->Get())->TeamId = i;
            FoundControllers.Add(Cast<AXYZPlayerController>(It->Get()));
            UniqueNetIds.Add(UniqueNetId);
            i++;
        }
        if(UniqueNetIds.Num() == MAX_PLAYERS)
        {
            UserRetriever->GetAllUserNetIdsToDisplayNames(UniqueNetIds);
            bRetrivedUsersInfo = UserRetriever->bRetrievedAllUsers;
            PlayerControllers = FoundControllers;
            TeamIdToPlayerController.Empty();
            for(AXYZPlayerController* PlayerController : PlayerControllers)
            {
                TeamIdToPlayerController.Add(PlayerController->TeamId, PlayerController);
            }
        }
    }else
    {
        TArray<AXYZPlayerController*> FoundControllers;
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            FoundControllers.Add(Cast<AXYZPlayerController>(It->Get()));
        }
        if(FoundControllers.Num() == MAX_PLAYERS)
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
                    TeamIdToPlayerController[Actor->TeamId]->FocusCameraOnLocation(Actor->GetActorLocation());
                }
            }
        }
    }
    
    if(TimeSinceStart <= LOADING_TIME)
    {
        TArray<TSharedRef<const FUniqueNetId>> UserNetIds;
        TArray<FString> UserNames;
        TArray<int32> Ratings;
        if (UserRetriever && UserStatRetriever) {
            for(AXYZPlayerController* PlayerController : PlayerControllers)
            {
                UserNetIds.Add(UserStatRetriever->GetControllerUniqueNetId(PlayerController).ToSharedRef());
            }
            if(!UserNetIds.IsEmpty())
            {
                UserStatRetriever->RetrieveStats(UserNetIds, {"rating"});
            }
            for(AXYZPlayerController* PlayerController : PlayerControllers)
            {
                TSharedPtr<const FUniqueNetId> PlayerNetId = UserRetriever->GetControllerUniqueNetId(PlayerController);
                if (PlayerNetId) {
                    FString UserNetId = PlayerNetId->ToString();
                    if (UserRetriever->UserDisplayNameMap.Contains(UserNetId)) {
                        UserNames.Add(UserRetriever->UserDisplayNameMap[UserNetId]);
                        Ratings.Add(UserStatRetriever->GetControllerStatInt32(PlayerController, "rating"));
                    }else
                    {
                        UserNames.Add("");
                        Ratings.Add(0);
                    }
                }else
                {
                    UserNames.Add("");
                }
            }
        }
        if(XYZGameState)
        {
            XYZGameState->UsernamesByTeamId = UserNames;
        }
        for(AXYZPlayerController* PlayerController : PlayerControllers)
        {
            PlayerController->UpdateLoadingScreen(UserNames, Ratings, TimeSinceStart/LOADING_TIME);
        }
    }else
    {
        XYZGameState->ProgressMatchState();
    }
}

void AXYZGameMode::Process(float DeltaSeconds)
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
    UpgradeManager->Process(DeltaSeconds);
    DeathManager->Process(DeltaSeconds);
    MapManager->Process(DeltaSeconds);
    MatchManager->Process(DeltaSeconds);

    TickCount++;
    bHasGameEnded = bHasGameEnded || NumOfPlayers < MAX_PLAYERS;

    if(bHasGameEnded)
    {
        XYZGameState->ProgressMatchState();
    }
}

void AXYZGameMode::ProcessCleanUp()
{
    for(AXYZPlayerController* PlayerController : PlayerControllers)
    {
        bool bHasWon = MatchManager->WinnerIndex == PlayerController->TeamId;
        int32 MatchStatus = bHasWon ? 1 : -1;
        FString WinsOrLossesStat = bHasWon ? "wins" : "losses";
        FString GamesStat = "games";
        FString RatingStat = "rating";
        int32 Rating = bHasWon ? RATING_GAIN : -1*RATING_GAIN;
        
        TSharedPtr<const FUniqueNetId> UniqueNetId = UserRetriever->GetControllerUniqueNetId(PlayerController);
        UserStatUpdater->UpdateInt32Stat(UniqueNetId.ToSharedRef(), WinsOrLossesStat, 1);
        UserStatUpdater->UpdateInt32Stat(UniqueNetId.ToSharedRef(), GamesStat, 1);
        UserStatUpdater->UpdateInt32Stat(UniqueNetId.ToSharedRef(), RatingStat, Rating);

        PlayerController->UpdateMatchStatus(MatchStatus);
    }

    XYZGameState->ProgressMatchState();
    
}

void AXYZGameMode::ProcessShutdown()
{
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        [this]() 
        {
            SessionHandler->DestroySession();
        },
        TIME_TO_DESTROY_SESSION, 
        false 
    );
    XYZGameState->ProgressMatchState();
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

    AXYZPlayerController* DisconnectedController = Cast<AXYZPlayerController>(InPlayerController);
    int32 OtherPlayedTeamId = DisconnectedController->TeamId == 1 ? 0 : 1;
    AXYZPlayerController* OtherPlayer = nullptr;

    for(AXYZPlayerController* PlayerController : PlayerControllers)
    {
        if(PlayerController != DisconnectedController)
        {
            OtherPlayer = PlayerController;
        }
    }

    bHasGameEnded = true;
    Cast<AXYZGameState>(GameState)->bHasGameEnded = true;

    if(OtherPlayer)
    {
        MatchManager->WinnerIndex = OtherPlayer->TeamId;
    }
    MatchManager->LoserIndex = DisconnectedController->TeamId;
}