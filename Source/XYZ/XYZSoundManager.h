#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZSoundManager.generated.h"

enum class ENotificationType : uint8;

UCLASS()
class XYZ_API AXYZSoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AXYZSoundManager();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TMap<ENotificationType, class USoundBase*> NotificationTypeToSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* BackgroundSound;
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayNotification(ENotificationType Notification);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayBackgroundMusic();
	
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class UAudioComponent* NotificationAudioComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class UAudioComponent* BackgroundAudioComponent;
	
	UPROPERTY()
	bool bIsPlayingBGMusic;
};