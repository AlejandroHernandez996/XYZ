// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuildingAbility.h"
#include "XYZBuilding.h"

void UXYZBuildingAbility::Activate() {
	OwningBuilding->EnqueueAbility(this);
}