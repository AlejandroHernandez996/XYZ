#include "XYZChatManager.h"

#include "XYZGameState.h"

UXYZChatManager::UXYZChatManager()
{
	Http = &FHttpModule::Get();
}

void UXYZChatManager::CreateLobby(FString LobbyId)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UXYZChatManager::OnCreateLobbyResponseReceived);
	Request->SetURL(CHAT_URL + CREATED_LOBBY_URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	Request->SetContentAsString("lobby_id=" + LobbyId);
	Request->ProcessRequest();
}

void UXYZChatManager::OnCreateLobbyResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("HTTP Status: %d"), Response->GetResponseCode());
		UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());
		bCreatedLobby = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed. Is the server running?"));
	}
}

void UXYZChatManager::SendMessage(FString LobbyId, FString Message)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UXYZChatManager::OnSendMessageResponseReceived);
	FString SendMessageUrl = CHAT_URL + SEND_MESSAGE_URL + FString::Printf(TEXT("/%s"), *LobbyId);
	Request->SetURL(SendMessageUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	Request->SetContentAsString(FString::Printf(TEXT("&message=%s"),*Message));
	Request->ProcessRequest();
}

void UXYZChatManager::OnSendMessageResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("HTTP Status: %d"), Response->GetResponseCode());
		UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed. Is the server running?"));
	}
}

void UXYZChatManager::GetMessages(FString LobbyId)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UXYZChatManager::OnGetMessagesResponseReceived);
	FString GetMessagesUrl = CHAT_URL + GET_MESSAGES_URL + FString::Printf(TEXT("/%s"), *LobbyId);
	Request->SetURL(GetMessagesUrl);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UXYZChatManager::OnGetMessagesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("HTTP Status: %d"), Response->GetResponseCode());
		UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());

		if(Response->GetContentAsString() != "Lobby not found")
		{
			GameState->LobbyMessages = FormatMessages(Response->GetContentAsString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed. Is the server running?"));
	}
}

FString UXYZChatManager::FormatMessages(const FString& JsonResponse)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonResponse);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* MessageArray;
		if (JsonObject->TryGetArrayField("messages", MessageArray))
		{
			FString FormattedMessages;
			for (const TSharedPtr<FJsonValue>& MessageValue : *MessageArray)
			{
				FormattedMessages += MessageValue->AsString() + TEXT("\n");
			}
			return FormattedMessages;
		}
	}
    
	return TEXT("Failed to format messages.");
}