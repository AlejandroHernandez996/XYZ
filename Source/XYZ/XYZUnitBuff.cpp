// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUnitBuff.h"
#include "XYZActor.h"
#include "XYZBuffAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZUnitBuff::Process(float DeltaTime)
{
	if(TotalTimeBuffed == 0.0f)
	{
		BuffActor(OwnerXYZActor);
		OwningAbility->bIsActive = true;
	}
	if(bDrainsEnergy)
	{
		OwnerXYZActor->Energy = FMath::Clamp(OwnerXYZActor->Energy-EnergyDrainPerSecond*DeltaTime,0,OwnerXYZActor->MaxEnergy);
	}
	if(bFlagForRemoval || (TotalTimeBuffed >= BuffDuration && BuffDuration != -1.0f) || (bDrainsEnergy && OwnerXYZActor->Energy <= 0.0f))
	{
		OwnerXYZActor->BuffsToRemove.Add(this);
		OwningAbility->bIsActive = false;
	}
	TotalTimeBuffed += DeltaTime;
}

void UXYZUnitBuff::BuffActor(AXYZActor* Actor)
{
	for(auto& KVP : BuffStats)
	{
		BuffActorStat(KVP.Key, KVP.Value, Actor);
	}
}

void UXYZUnitBuff::DebuffActor(AXYZActor* Actor)
{
	for(auto& KVP : DebuffStats)
	{
		BuffActorStat(KVP.Key, KVP.Value, Actor);
	}
}

void UXYZUnitBuff::BuffActorStat(EXYZStat Stat, float StatGain, AXYZActor* Actor)
{
	if(!Actor) return;
	
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
	case EXYZStat::ATTACK:
		Actor->AttackDamage += StatGain;
		break;
	case EXYZStat::MAX_ENERGY:
		Actor->MaxEnergy += StatGain;
		break;
	case EXYZStat::ENERGY:
		Actor->Energy += StatGain;
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
	case EXYZStat::CLOAK:
		Actor->SetIsCloaked(StatGain != 0.0f);
		break;
	default: ;
	}
}

