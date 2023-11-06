// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAreaOfEffect.h"
#include "XYZGameMode.h"
#include "XYZMapManager.h"
#include "XYZMatchStatsManager.h"
#include "XYZResourceActor.h"
#include "XYZUnitBuff.h"

// Sets default values
AXYZAreaOfEffect::AXYZAreaOfEffect()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void AXYZAreaOfEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXYZAreaOfEffect::InitBuffs()
{
	for(TSubclassOf<UXYZUnitBuff> BuffTemplate : TeamBuffsToApplyTemplate)
	{
		FName BuffName = FName(GetName().Append(FGuid::NewGuid().ToString()));
		UXYZUnitBuff* NewBuff =  NewObject<UXYZUnitBuff>(this, BuffTemplate, BuffName);
		if(NewBuff)
		{
			TeamBuffsToApply.Add(NewBuff);
		}
	}

	for(TSubclassOf<UXYZUnitBuff> BuffTemplate : EnemyBuffsToApplyTemplate)
	{
		FName BuffName = FName(GetName().Append(FGuid::NewGuid().ToString()));
		UXYZUnitBuff* NewBuff =  NewObject<UXYZUnitBuff>(this, BuffTemplate, BuffName);
		if(NewBuff)
		{
			EnemyBuffsToApply.Add(NewBuff);
		}
	}
}

void AXYZAreaOfEffect::Process(float DeltaTime)
{
	if(CurrentDuration >= MaxDuration || bIsDone)
	{
		bIsDone = true;
		return;
	}

	FIntVector2 CenterGrid = MapManager->GetGridCoordinate(GetActorLocation());
	TSet<AXYZActor*> InsideActors = MapManager->FindActorsInRange(CenterGrid, AbilityRadius);

	TSet<AXYZActor*> InsideActorsToRemove;
	for(AXYZActor* Actor: InsideActors)
	{
		if(Actor->IsA(AXYZResourceActor::StaticClass()))
		{
			InsideActorsToRemove.Add(Actor);
		}
	}
	InsideActors = InsideActors.Difference(InsideActorsToRemove);
	TSet<AXYZActor*> OutsideActors = InsideActorsLastTick.Difference(InsideActors);

	ProcessInsideActors(InsideActors);
	ProcessOutsideActors(OutsideActors);
	InsideActorsLastTick = InsideActors;
	if(Damage != 0.0f && ((bConstantDamage || CurrentDuration == 0.0f) || TimeSinceLastDamageTick >= DamageRate))
	{
		DamageInsideActors(InsideActors);
		TimeSinceLastDamageTick = 0.0f;
	}
	TimeSinceLastDamageTick += DeltaTime;
	CurrentDuration += DeltaTime;
}

void AXYZAreaOfEffect::DamageInsideActors(TSet<AXYZActor*> ActorsToDamage)
{
	for(AXYZActor* Actor : ActorsToDamage)
	{
		if(!Actor) continue;
		if (Actor->bIsFlying && !bCanHitAir) {
			continue;
		}

		bool bHasDamaged = DamagedActors.Contains(Actor);
		if (bHasDamaged && !bConstantDamage) {
			continue;
		}

		bool bIsAlly = Actor->TeamId == TeamId;
		if (!bIsAlly || bDamagesAllies) {
			if(Actor->Health > 0.0f && Actor->Health - Damage <= 0.0f)
			{
				Actor->GetWorld()->GetAuthGameMode<AXYZGameMode>()->MatchStatsManager->AddIntStat(1,EMatchStatType::UNITS_KILLED, TeamId);
			}
			Actor->Health = FMath::Clamp(Actor->Health - Damage, 0, Actor->MaxHealth);
			DamagedActors.Add(Actor);
		}
	}
}

void AXYZAreaOfEffect::ProcessInsideActors(TSet<AXYZActor*> Actors)
{
	for(AXYZActor* Actor : Actors)
	{
		if(!Actor) continue;
		if(Actor->TeamId == TeamId)
		{
			for(UXYZUnitBuff* UnitBuff : TeamBuffsToApply)
			{
				if(!ActorsBuffed.Contains(Actor) || UnitBuff->bIsStackable)
				{
					UnitBuff->BuffActor(Actor);
				}
			}
		}
		else
		{
			for(UXYZUnitBuff* UnitBuff : EnemyBuffsToApply)
			{
				if(!ActorsBuffed.Contains(Actor) || UnitBuff->bIsStackable)
				{
					UnitBuff->BuffActor(Actor);
				}
			}
		}
		ActorsBuffed.Add(Actor);
	}
}

void AXYZAreaOfEffect::ProcessOutsideActors(TSet<AXYZActor*> Actors)
{
	for(AXYZActor* Actor : Actors)
	{
		if(!Actor) continue;
		if(ActorsBuffed.Contains(Actor))
		{
			if(Actor->TeamId == TeamId)
			{
			
				for(UXYZUnitBuff* UnitBuff : TeamBuffsToApply)
				{
					UnitBuff->DebuffActor(Actor);
				}
			}
			else
			{
				for(UXYZUnitBuff* UnitBuff : EnemyBuffsToApply)
				{
					UnitBuff->DebuffActor(Actor);
				}
			}
			ActorsBuffed.Remove(Actor);
		}
	}
}

void AXYZAreaOfEffect::EndAOE()
{
	for(AXYZActor* Actor : ActorsBuffed)
	{
		if(!Actor) continue;
		if(ActorsBuffed.Contains(Actor))
		{
			if(Actor->TeamId == TeamId)
			{
			
				for(UXYZUnitBuff* UnitBuff : TeamBuffsToApply)
				{
					UnitBuff->DebuffActor(Actor);
				}
			}
			else
			{
				for(UXYZUnitBuff* UnitBuff : EnemyBuffsToApply)
				{
					UnitBuff->DebuffActor(Actor);
				}
			}
		}
	}
	ActorsBuffed.Empty();
	Destroy();
}