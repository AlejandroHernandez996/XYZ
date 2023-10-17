// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "XYZUpgradeAbility.h"
#include "UObject/NoExportTypes.h"
#include "XYZUpgradeManager.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API UXYZUpgradeManager : public UObject, public IProcessable
{
	GENERATED_BODY()
public:
	void Process(float DeltaTime) override;

	TArray<TMap<int32, class UXYZUpgradeAbility*>> UpgradesByTeam{ {},{}};

	TArray<TSet<int32>> UpgradesInResearch = { {},{}};

	UPROPERTY()
	TSet<UXYZUpgradeAbility*> UpgradeAbilities;

	UPROPERTY()
	TSet<UXYZUpgradeAbility*> UpgradeAbilitiesToRemove;
	
	UPROPERTY()
	class AXYZGameState* GameState;

	UFUNCTION()
	bool ContainsUpgrade(UXYZUpgradeAbility* UpgradeAbility);
	UFUNCTION()
	bool HasResearched(int32 AbilityId, int32 TeamId);
	UFUNCTION()
	bool IsUpgradeBeingResearched(UXYZUpgradeAbility* UpgradeAbility);
	UFUNCTION()
	void RemoveUpgradeFromResearch(UXYZUpgradeAbility* UpgradeAbility);
	UFUNCTION()
	void AddUpgradeToResearch(UXYZUpgradeAbility* UpgradeAbility);

	UFUNCTION()
	void AddUpgradeAbility(UXYZUpgradeAbility* Ability);
};
