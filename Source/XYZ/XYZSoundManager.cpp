#include "XYZSoundManager.h"
#include "Components/AudioComponent.h"

AXYZSoundManager::AXYZSoundManager()
{
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AXYZSoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void AXYZSoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXYZSoundManager::PlaySound(ESoundTypes SoundType)
{
	if (SoundTypeToSound.Contains(SoundType))
	{
		USoundBase* SoundToPlay = SoundTypeToSound[SoundType];
		if (SoundToPlay)
		{
			AudioComponent->SetSound(SoundToPlay);
			AudioComponent->Play();
		}
	}
}