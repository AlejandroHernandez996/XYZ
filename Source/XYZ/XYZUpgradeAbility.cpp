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

void UXYZUpgradeAbility::UpgradeActorStat(EXYZStat Stat, float StatGain, AXYZActor* Actor)
{
	switch(Stat)
	{
	case EXYZStat::ARMOR:
		Actor->Armor += StatGain;
		break;
	case EXYZStat::HEALTH:
		Actor->Health += StatGain;
		break;
	case EXYZStat::MAX_HEALTH:
		Actor->MaxHealth += StatGain;
		break;
	case EXYZStat::ENERGY:
		Actor->Energy += StatGain;
		break;
	case EXYZStat::MAX_ENERGY:
		Actor->MaxEnergy += StatGain;
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

void UXYZUpgradeAbility::DowngradeActor(AXYZActor* Actor)
{
	for(auto& KVP : StatGainMap)
	{
		UpgradeActorStat(KVP.Key, -1*KVP.Value, Actor);
	}
}

UXYZUpgradeAbility* UXYZUpgradeAbility::DeepCopy()
{
	FString NewObjectName = this->GetName() + "_CacheCopy_" + FString::FromInt(this->CurrentStage);
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
	UpgradeAbilityDeepCopy->GasCost = GasCost;
	UpgradeAbilityDeepCopy->SupplyCost = SupplyCost;
	UpgradeAbilityDeepCopy->ActorRequirements = ActorRequirements;
	UpgradeAbilityDeepCopy->OwningActor = OwningActor;

	return UpgradeAbilityDeepCopy;
}

void UXYZUpgradeAbility::UpdateStage(int32 Stage)
{
	if(Stage > MaxStage || Stage == CurrentStage || Stage < 0) return;
	CurrentStage = Stage;
	Name = NameByStage[Stage];
	MineralCost = MineralCostByStage[Stage];
	GasCost = GasCostByStage[Stage];
	AbilityImage = ImagesByStage[Stage];
}
