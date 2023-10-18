// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "XYZProjectileManager.generated.h"

class AXYZProjectile;
/**
 * 
 */
UCLASS()
class XYZ_API UXYZProjectileManager : public UObject, public IProcessable
{
	GENERATED_BODY()

public:
	void Process(float DeltaTime) override;

	UPROPERTY()
	TSet<AXYZProjectile*> ActiveProjectiles;

	UPROPERTY()
	TSet<AXYZProjectile*> ProjectileToDestroy;

	UFUNCTION()
	void SpawnProjectile(TSubclassOf<AXYZProjectile> Projectile, FVector TargetLocation, AXYZActor* TargetActor, AXYZActor* OwningActor);
};
