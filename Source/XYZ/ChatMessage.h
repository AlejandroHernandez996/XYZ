#pragma once

#include "CoreMinimal.h"
#include "ChatMessage.generated.h"

USTRUCT()
struct FChatMessage
{
	GENERATED_BODY()

	UPROPERTY()
	FString LobbyId;
	UPROPERTY()
	FString MessageContent;
	FString ToJson() const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField(TEXT("LobbyId"), LobbyId);
		JsonObject->SetStringField(TEXT("MessageContent"), MessageContent);

		FString OutputString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

		return OutputString;
	}
};