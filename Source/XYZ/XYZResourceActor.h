// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XYZActor.h"
#include "XYZResourceType.h"
#include "XYZResourceActor.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AXYZResourceActor : public AXYZActor
{
	GENERATED_BODY()
public:
	EXYZResourceType ResourceType = EXYZResourceType::MINERAL;
};
