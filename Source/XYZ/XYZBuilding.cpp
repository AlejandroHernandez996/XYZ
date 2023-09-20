// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZBuilding.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"

void AXYZBuilding::BeginPlay() {
    Super::BeginPlay();
    bCanMove = false;
}

void AXYZBuilding::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AXYZBuilding, RallyPoint);
}
