// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "UObject/NoExportTypes.h"
#include "XYZAreaOfEffectManager.generated.h"

class UXYZTargetAreaAbility;
/**
 * 
 */
UCLASS()
class XYZ_API UXYZAreaOfEffectManager : public UObject, public IProcessable
{
	GENERATED_BODY()

public:
	virtual void Process(float DeltaTime) override;

	UPROPERTY()
	TSet<class AXYZAreaOfEffect*> ActiveAOEs;
	UPROPERTY()
	TSet<class AXYZAreaOfEffect*> AOEsToDestroy;

	UFUNCTION()
	void CreateAOE(TSubclassOf<AXYZAreaOfEffect> AOETemplate, int32 TeamId, FVector TargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UXYZMapManager* MapManager;
};
