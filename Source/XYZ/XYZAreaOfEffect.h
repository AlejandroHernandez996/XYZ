// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "GameFramework/Actor.h"
#include "XYZAreaOfEffect.generated.h"

UCLASS(Blueprintable)
class XYZ_API AXYZAreaOfEffect : public AActor, public IProcessable
{
	GENERATED_BODY()
	
public:	
	AXYZAreaOfEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Process(float DeltaTime) override;

	UFUNCTION()
	void InitBuffs();
	UFUNCTION()
	void ProcessInsideActors(TSet<AXYZActor*> Actors);
	UFUNCTION()
	void ProcessOutsideActors(TSet<AXYZActor*> Actors);
	void EndAOE();

	UPROPERTY()
	bool bIsDone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<TSubclassOf<class UXYZUnitBuff>> TeamBuffsToApplyTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<TSubclassOf<UXYZUnitBuff>> EnemyBuffsToApplyTemplate;
	UPROPERTY()
	TSet<UXYZUnitBuff*> TeamBuffsToApply;
	UPROPERTY()
	TSet<UXYZUnitBuff*> EnemyBuffsToApply;
	UPROPERTY()
	TSet<class AXYZActor*> ActorsBuffed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDuration;
	UPROPERTY()
	float CurrentDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityRadius = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToLive = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeSinceLastDamageTick;
	UPROPERTY()
	TSet<class AXYZActor*> InsideActorsLastTick;
	UPROPERTY()
	class UXYZMapManager* MapManager;
	
	UPROPERTY()
	int32 TeamId = -1;
};
