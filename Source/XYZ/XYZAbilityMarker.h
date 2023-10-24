// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZAbilityMarker.generated.h"

UCLASS()
class XYZ_API AXYZAbilityMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	AXYZAbilityMarker();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDecalComponent* DecalComponent;
};
