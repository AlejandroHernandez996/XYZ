// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZTargetAreaAbility.h"

#include "XYZActor.h"
#include "XYZAreaOfEffectManager.h"
#include "XYZGameMode.h"

bool UXYZTargetAreaAbility::Activate()
{
	if(Super::Activate())
	{
		OwningActor->Energy = FMath::Clamp(OwningActor->Energy-EnergyCost,0.0f,OwningActor->MaxEnergy);
		OwningActor->Health = FMath::Clamp(OwningActor->Health-HealthCost,0.0f,OwningActor->MaxHealth);
		GetWorld()->GetAuthGameMode<AXYZGameMode>()->AreaOfEffectManager->CreateAOE(AOETemplate,OwningActor->TeamId, TargetLocation);
		return true;
	}
	return false;
}


