// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZUnitBuff.h"
#include "XYZActor.h"
#include "GameFramework/CharacterMovementComponent.h"

void UXYZUnitBuff::Process(float DeltaTime)
{
	if(TotalTimeBuffed == 0.0f)
	{
		BuffActor(OwnerXYZActor);
	}

	if(TotalTimeBuffed >= BuffDuration && BuffDuration != -1.0f)
	{
		OwnerXYZActor->BuffsToRemove.Add(this);
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
	default: ;
	}
}

