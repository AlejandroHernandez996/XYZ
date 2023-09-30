// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZRuntimeVolumeManager.h"

#include "EngineUtils.h"
#include "XYZPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "VT/RuntimeVirtualTextureVolume.h"

// Sets default values
AXYZRuntimeVolumeManager::AXYZRuntimeVolumeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AXYZRuntimeVolumeManager::BeginPlay()
{
	Super::BeginPlay();
	if(GetLocalRole() == ROLE_Authority) return;
	UWorld* World = GetWorld();
	if (World)
	{
		for (TActorIterator<ARuntimeVirtualTextureVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ARuntimeVirtualTextureVolume* Volume = *ActorItr;
			if (Volume)
			{
				RuntimeVolumes.Add(Volume);
			}
		}
	}
	RuntimeVolumes.Sort([](ARuntimeVirtualTextureVolume& A, ARuntimeVirtualTextureVolume& B) {
	return A.GetFName().ToString() < B.GetFName().ToString();
	});
}

void AXYZRuntimeVolumeManager::Tick(float DeltaSeconds)
{
	if(bStopTickFlag || GetLocalRole() == ROLE_Authority) return;
	
	AXYZPlayerController* LocalPlayer = Cast<AXYZPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if(!LocalPlayer || LocalPlayer->TeamId == -1) return;
	RuntimeVolumes[LocalPlayer->TeamId == 1 ? 0 : 1]->Destroy();
	bStopTickFlag = true;
}

