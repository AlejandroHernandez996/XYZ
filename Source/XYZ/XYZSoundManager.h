#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZSoundManager.generated.h"

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
	TMap<ESoundTypes, class USoundBase*> SoundTypeToSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* BackgroundSound;
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayNotification(ESoundTypes SoundType);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayBackgroundMusic();
	
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class UAudioComponent* NotificationAudioComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class UAudioComponent* BackgroundAudioComponent;
	
	UPROPERTY()
	bool bIsPlayingBGMusic;
};