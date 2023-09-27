// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"
#include "Json.h"
#include "LoginHandler.h"
#include "SessionHandler.h"
#include "UserInfoRetriver.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "UserStatRetriever.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"

AMenuGameMode::AMenuGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.TickInterval = 1.0f;
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();
    bUseSeamlessTravel = true;
    LoginHandler = NewObject<ULoginHandler>(this);
    SessionHandler = NewObject<USessionHandler>(this);
    UserStatRetriever = NewObject<UUserStatRetriever>(this);
    UserRetriever = NewObject<UUserInfoRetriver>(this);
}

void AMenuGameMode::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

    if (SessionHandler->bFailedSession) {
        SessionHandler->bFailedSession = false;
        SessionHandler->bHasFoundSession = false;
        SessionHandler->bHasJoinedSession = false;
        MenuState = EMainMenuStateEnum::LOGGED_IN;
    }
    switch (MenuState)
    {
        case EMainMenuStateEnum::PRE_LOGGING_IN:
            LoginHandler->Login();
            MenuState = EMainMenuStateEnum::LOGGING_IN;
            break;
        case EMainMenuStateEnum::LOGGING_IN:
            if (LoginHandler->bIsLoggedIn) {
                MenuState = EMainMenuStateEnum::LOGGED_IN;
            }
            break;
        case EMainMenuStateEnum::LOGGED_IN:
            if (UserRetriever->UserDisplayNameMap.IsEmpty()) {
                UserRetriever->SetUserNetIdsToDisplayName(GetWorld()->GetFirstPlayerController<APlayerController>());
            }
            break;
        case EMainMenuStateEnum::FINDING_SESSION:
            SessionHandler->FindSession();
            if (SessionHandler->bHasFoundSession) {
                MenuState = EMainMenuStateEnum::FOUND_SESSION;
            }
            break;
        case EMainMenuStateEnum::FOUND_SESSION:
            MenuState = EMainMenuStateEnum::JOINING_SESSION;
            SessionHandler->JoinSession();
            break;
        case EMainMenuStateEnum::JOINING_SESSION:
            if (SessionHandler->bHasJoinedSession) {
                MenuState = EMainMenuStateEnum::JOINED_SESSION;
            }
            break;
        case EMainMenuStateEnum::JOINED_SESSION:
            if (GEngine != nullptr)
            {
                FURL NewURL(nullptr, *SessionHandler->GetConnectionInfo(), ETravelType::TRAVEL_Absolute);
                FString BrowseError;
                if (GEngine->Browse(GEngine->GetWorldContextFromWorldChecked(this->GetWorld()), NewURL, BrowseError) ==
                    EBrowseReturnVal::Failure)
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to start browse: %s"), *BrowseError);
                }
                else {
                    MenuState = EMainMenuStateEnum::CONNECTING_SESSION;
                }
            }
            break;
        default:
            break;
    }
    if (LoginHandler->bIsLoggedIn && !bRetrievingStats) {
       // TSharedRef<const FUniqueNetId> UserNetId = UserRetriever->GetControllerUniqueNetId(GetWorld()->GetFirstPlayerController<APlayerController>()).ToSharedRef();
       // TArray<TSharedRef<const FUniqueNetId>> Users;
       // TArray<FString> Stats;
       // Stats.Add("player_wins");
       // Users.Add(UserNetId);
       // UserStatRetriever->RetrieveStats(Users, Stats);
       // bRetrievingStats = true;
    }
    
}

void AMenuGameMode::FindSession() {
    if (MenuState == EMainMenuStateEnum::LOGGED_IN) {
        MenuState = EMainMenuStateEnum::FINDING_SESSION;
    }
}

void AMenuGameMode::CancelSession() {
    if (MenuState == EMainMenuStateEnum::FINDING_SESSION) {
        MenuState = EMainMenuStateEnum::LOGGED_IN;
        SessionHandler->bFailedSession = false;
        SessionHandler->bHasFoundSession = false;
        SessionHandler->bHasJoinedSession = false;
        SessionHandler->bCancelFindSessionFlag = true;
    }
}

FString AMenuGameMode::GetUsername() {
    if (UserRetriever) {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController<APlayerController>();
        TSharedPtr<const FUniqueNetId> PlayerNetId = UserRetriever->GetControllerUniqueNetId(PlayerController);
        if (PlayerNetId) {
            FString UserNetId = PlayerNetId->ToString();
            if (UserRetriever->UserDisplayNameMap.Contains(UserNetId)) {
                return UserRetriever->UserDisplayNameMap[UserNetId];
            }
        }
    }
    return "N/A";
}

FString AMenuGameMode::GetStateToString() {
    switch (MenuState) {
    case EMainMenuStateEnum::PRE_LOGGING_IN:
        return "Not Connected!";
        break;
    case EMainMenuStateEnum::LOGGING_IN:
        return "Logging In!";
        break;
    case EMainMenuStateEnum::LOGGED_IN:
        return "Logged In!";
        break;
    case EMainMenuStateEnum::FINDING_SESSION:
        return "Finding Session!";
        break;
    case EMainMenuStateEnum::FOUND_SESSION:
        return "Found Session!";
        break;
    case EMainMenuStateEnum::JOINING_SESSION:
        return "Joining Session!";
        break;
    case EMainMenuStateEnum::JOINED_SESSION:
        return "Joined Session!";
        break;
    case EMainMenuStateEnum::CONNECTING_SESSION:
        return "Connecting To Session!";
        break;
    case EMainMenuStateEnum::CONNECTED_SESSION:
        return "Connected To Session!";
        break;
    default:
        return "STATE DOESN'T EXIST FOR MENU";
    }
}