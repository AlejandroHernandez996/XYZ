#include "XYZChatManager.h"

#include "ChatMessage.h"
#include "IWebSocket.h"
#include "WebSocketsModule.h"
#include "XYZGameState.h"

UXYZChatManager::UXYZChatManager()
{
}

void UXYZChatManager::ConnectToChatServer()
{
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(CHAT_WSS);

	WebSocket->OnConnected().AddUObject(this, &UXYZChatManager::HandleWebSocketConnected);
	WebSocket->OnConnectionError().AddUObject(this, &UXYZChatManager::HandleWebSocketConnectionError);
	WebSocket->OnClosed().AddUObject(this, &UXYZChatManager::HandleWebSocketClosed);
	WebSocket->OnMessage().AddUObject(this, &UXYZChatManager::HandleWebSocketMessageReceived);

	if (WebSocket.IsValid())
	{
		WebSocket->Connect();
	}
}

void UXYZChatManager::SendMessage(FString LobbyId, FString PlayerMessage)
{
	if (WebSocket.IsValid() && WebSocket->IsConnected())
	{
		FChatMessage ChatMessage;
		ChatMessage.LobbyId = LobbyId;
		ChatMessage.MessageContent = PlayerMessage;
		WebSocket->Send(ChatMessage.ToJson());
	}
}

void UXYZChatManager::HandleWebSocketConnected()
{
	UE_LOG(LogTemp, Warning, TEXT("WebSocket Connected!"));
	SendMessage(GameState->ChatLobbyId, "");
}

void UXYZChatManager::HandleWebSocketConnectionError(const FString& Error)
{
	UE_LOG(LogTemp, Error, TEXT("WebSocket Connection Error: %s"), *Error);
}

void UXYZChatManager::HandleWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	UE_LOG(LogTemp, Warning, TEXT("WebSocket Closed! Status: %d, Reason: %s"), StatusCode, *Reason);
}

void UXYZChatManager::HandleWebSocketMessageReceived(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("Received WebSocket Message: %s"), *Message);
	if(!Message.IsEmpty())
	{
		GameState->LobbyMessages += "\n" + Message;
	}
}

FString UXYZChatManager::FormatMessage(const FString& JsonResponse)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonResponse);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString Message;
		if (JsonObject->TryGetStringField(TEXT("message"), Message))
		{
			return Message;
		}
	}
	return TEXT("Failed to format message.");
}