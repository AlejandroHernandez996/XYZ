#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZChatManager.generated.h"

class IWebSocket;

UCLASS()
class XYZ_API UXYZChatManager : public UObject
{
	GENERATED_BODY()

public:
	UXYZChatManager();
	UPROPERTY()
	class AXYZGameState* GameState;
	FString CHAT_WSS = "wss://xyz-ue5.uc.r.appspot.com/";
	void SendMessage(FString LobbyId, FString Message);
	void HandleWebSocketConnected();
	void HandleWebSocketConnectionError(const FString& Error);
	void HandleWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	FString GetRichChatMessage(FString String);
	void HandleWebSocketMessageReceived(const FString& Message);
	void ConnectToChatServer();
	
	bool bCreatedLobby;
private:
	TSharedPtr<IWebSocket> WebSocket;
};