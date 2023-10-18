// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZProjectileManager.h"

#include "XYZActor.h"
#include "XYZProjectile.h"

void UXYZProjectileManager::Process(float DeltaTime)
{
	for(AXYZProjectile* Projectile : ProjectileToDestroy)
	{
		ActiveProjectiles.Remove(Projectile);
		Projectile->Destroy();
	}
	ProjectileToDestroy.Empty();

	for(AXYZProjectile* Projectile : ActiveProjectiles)
	{
		if(Projectile->bDestroyFlag)
		{
			ProjectileToDestroy.Add(Projectile);
		}else
		{
			Projectile->Process(DeltaTime);
		}
	}
}

void UXYZProjectileManager::SpawnProjectile(TSubclassOf<AXYZProjectile> ProjectileTemplate, FVector TargetLocation,
	AXYZActor* TargetActor, AXYZActor* OwningActor)
{
	if(!ProjectileTemplate || !OwningActor) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AXYZProjectile* SpawnedProjectile = OwningActor->GetWorld()->SpawnActor<AXYZProjectile>(ProjectileTemplate, OwningActor->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	SpawnedProjectile->TargetActor = TargetActor;
	SpawnedProjectile->OwningActor = OwningActor;
	SpawnedProjectile->TargetLocation = TargetLocation;
	ActiveProjectiles.Add(SpawnedProjectile);
}
