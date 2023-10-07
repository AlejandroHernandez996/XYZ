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

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySound(ESoundTypes SoundType);

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class UAudioComponent* AudioComponent;
};