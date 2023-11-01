#include "XYZSoundManager.h"
#include "Components/AudioComponent.h"

AXYZSoundManager::AXYZSoundManager()
{
	PrimaryActorTick.bCanEverTick = true;
	NotificationAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("NotificationAudioComponent"));
	BackgroundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundAudioComponent"));

}

void AXYZSoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void AXYZSoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AXYZSoundManager::PlayNotification(ENotificationType NotificationType)
{
	if (NotificationTypeToSound.Contains(NotificationType))
	{
		USoundBase* SoundToPlay = NotificationTypeToSound[NotificationType];
		if (SoundToPlay)
		{
			NotificationAudioComponent->SetSound(SoundToPlay);
			NotificationAudioComponent->Play();
		}
	}
}

void AXYZSoundManager::PlayBackgroundMusic()
{
	if(!bIsPlayingBGMusic && BackgroundAudioComponent && BackgroundSound)
	{
		BackgroundAudioComponent->SetSound(BackgroundSound);
		BackgroundAudioComponent->Play();
		bIsPlayingBGMusic = true;
	}
}
