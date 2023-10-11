#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "XYZChatManager.generated.h"

UCLASS()
class XYZ_API UXYZChatManager : public UObject
{
	GENERATED_BODY()

public:
	UXYZChatManager();
	UPROPERTY()
	class AXYZGameState* GameState;

	void CreateLobby(FString LobbyId);
	void SendMessage(FString LobbyId, FString Message);
	void GetMessages(FString LobbyId);
	bool bCreatedLobby;
private:
	FHttpModule* Http;
	FString CHAT_URL = "https://xyz-ue5.uc.r.appspot.com/";
	FString CREATED_LOBBY_URL = "create-lobby";
	FString SEND_MESSAGE_URL = "send-message";
	FString GET_MESSAGES_URL = "get-messages";
	
	void OnCreateLobbyResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnSendMessageResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetMessagesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString FormatMessages(const FString& JsonResponse);
};