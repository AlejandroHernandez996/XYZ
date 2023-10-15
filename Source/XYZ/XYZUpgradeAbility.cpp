// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUpgradeAbility.h"

#include "XYZActor.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZUpgradeAbility::UpgradeActor(AXYZActor* Actor)
{
	for(auto& KVP : StatGainMap)
	{
		UpgradeActorStat(KVP.Key, KVP.Value, Actor);
	}
}

void UXYZUpgradeAbility::UpgradeActorStat(EXYZStat Stat, int32 StatGain, AXYZActor* Actor)
{
	switch(Stat)
	{
	case EXYZStat::ARMOR:
		Actor->Armor += StatGain;
		break;
	case EXYZStat::HEALTH:
		Actor->MaxHealth += StatGain;
		Actor->Health += StatGain;
		break;
	case EXYZStat::ATTACK:
		Actor->AttackDamage += StatGain;
		break;
	case EXYZStat::ATTACK_RANGE:
		Actor->AttackRange += StatGain;
		break;
	case EXYZStat::VISION_RANGE:
		Actor->VisionRange += StatGain;
		break;
	case EXYZStat::ATTACK_RATE:
		Actor->AttackRate += StatGain;
		break;
	case EXYZStat::MOVEMENT_SPEED:
		Actor->GetCharacterMovement()->MaxWalkSpeed += StatGain;
		break;
	default: ;
	}
}

UXYZUpgradeAbility* UXYZUpgradeAbility::DeepCopy()
{
	FString NewObjectName = this->GetName() + "_CacheCopy";
	UXYZUpgradeAbility* UpgradeAbilityDeepCopy = NewObject<UXYZUpgradeAbility>(this, UXYZUpgradeAbility::StaticClass(), *NewObjectName);
	
	UpgradeAbilityDeepCopy->TeamId = TeamId;
	UpgradeAbilityDeepCopy->CurrentStage = CurrentStage;
	UpgradeAbilityDeepCopy->MaxStage = MaxStage;
	UpgradeAbilityDeepCopy->StatGainMap = StatGainMap;
	UpgradeAbilityDeepCopy->AffectedActorIds = AffectedActorIds;
	UpgradeAbilityDeepCopy->BuildTime = BuildTime;
	UpgradeAbilityDeepCopy->BuildTime = BuildTime;
	UpgradeAbilityDeepCopy->OwningBuilding = OwningBuilding;
	UpgradeAbilityDeepCopy->bCanCancel = bCanCancel;
	UpgradeAbilityDeepCopy->ID = ID;
	UpgradeAbilityDeepCopy->Name = Name;
	UpgradeAbilityDeepCopy->AbilityImage = AbilityImage;
	UpgradeAbilityDeepCopy->MineralCost = MineralCost;
	UpgradeAbilityDeepCopy->SupplyCost = SupplyCost;
	UpgradeAbilityDeepCopy->ActorRequirements = ActorRequirements;
	UpgradeAbilityDeepCopy->OwningActor = OwningActor;

	return UpgradeAbilityDeepCopy;
}
