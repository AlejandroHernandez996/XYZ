// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuildingAbility.h"
#include "XYZBuilding.h"

bool UXYZBuildingAbility::Activate() {
	if(Super::Activate())
	{
		if(!OwningBuilding) return false;
		OwningBuilding->EnqueueAbility(this);
		return true;
	}
	return false;
}