// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZAreaOfEffect.h"

#include "XYZMapManager.h"
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
	TSet<AXYZActor*> OutsideActors = InsideActorsLastTick.Difference(InsideActors);

	ProcessInsideActors(InsideActors);
	ProcessOutsideActors(OutsideActors);
	InsideActorsLastTick = InsideActors;
	CurrentDuration += DeltaTime;
}

void AXYZAreaOfEffect::ProcessInsideActors(TSet<AXYZActor*> Actors)
{
	for(AXYZActor* Actor : Actors)
	{
		if(!ActorsBuffed.Contains(Actor))
		{
			if(Actor->TeamId == TeamId)
			{
			
				for(UXYZUnitBuff* UnitBuff : TeamBuffsToApply)
				{
					UnitBuff->BuffActor(Actor);
				}
			}
			else
			{
				for(UXYZUnitBuff* UnitBuff : EnemyBuffsToApply)
				{
					UnitBuff->BuffActor(Actor);
				}
			}
			ActorsBuffed.Add(Actor);
		}
	}
}

void AXYZAreaOfEffect::ProcessOutsideActors(TSet<AXYZActor*> Actors)
{
	for(AXYZActor* Actor : Actors)
	{
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