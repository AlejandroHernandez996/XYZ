// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuffAbility.h"

#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZUnitBuff.h"
#include "XYZUpgradeManager.h"

bool UXYZBuffAbility::Activate()
{
	if(!Super::Activate())
	{
		return false;
	}

	if(OwningActor)
	{
		UXYZUpgradeManager* UpgradeManager = OwningActor->GetWorld()->GetAuthGameMode<AXYZGameMode>()->UpgradeManager;
		for(int32 RequiredUpgrade : RequiredUpgradeIds)
		{
			if(!UpgradeManager->HasResearched(RequiredUpgrade, OwningActor->TeamId))
			{
				return false;
			}
		}
		FName BuffName = FName(*Name.AppendChar('_').Append(OwningActor->DisplayName).Append(FGuid::NewGuid().ToString()));
		UXYZUnitBuff* NewBuff =  NewObject<UXYZUnitBuff>(OwningActor, BuffTemplate, BuffName);
		NewBuff->OwnerXYZActor = OwningActor;
		OwningActor->AddBuff(NewBuff);
		return true;
	}
	return false;
}
