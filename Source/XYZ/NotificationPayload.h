#pragma once

#include "CoreMinimal.h"
#include "NotificationPayload.generated.h"

enum class ENotificationType : uint8;

USTRUCT(BlueprintType)
struct FNotificationPayload
{
	GENERATED_BODY()

	UPROPERTY()
	ENotificationType NotificationType;

	UPROPERTY()
	class AXYZActor* NotificationTriggerActor;

};