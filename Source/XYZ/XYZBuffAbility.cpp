// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuffAbility.h"

#include "NotificationPayload.h"
#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZPlayerController.h"
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
				FNotificationPayload NotificationPayload = FNotificationPayload();
				NotificationPayload.NotificationType = ENotificationType::NOTIFY_UPGRADE_REQUIRED;
				OwningActor->OwningPlayerController->SendNotification(NotificationPayload);
				return false;
			}
		}
		if(bIsToggleable && bIsActive)
		{
			for(UXYZUnitBuff* Buff : OwningActor->ActiveBuffs)
			{
				if(Buff->OwningAbility == this)
				{
					Buff->bFlagForRemoval = true;
					return true;
				}
			}
			return false;
		}
		OwningActor->Energy = FMath::Clamp(OwningActor->Energy-EnergyCost,0.0f,OwningActor->MaxEnergy);
		FString BuffPrefixName = Name;
		FName BuffName = FName(*BuffPrefixName.AppendChar('_').Append(FGuid::NewGuid().ToString()));
		UXYZUnitBuff* NewBuff =  NewObject<UXYZUnitBuff>(OwningActor, BuffTemplate, BuffName);
		NewBuff->OwningAbility = this;
		NewBuff->OwnerXYZActor = OwningActor;
		OwningActor->AddBuff(NewBuff);
		return true;
	}
	return false;
}
