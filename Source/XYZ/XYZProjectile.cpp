// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZProjectile.h"
#include "XYZActor.h"
#include "Net/UnrealNetwork.h"

AXYZProjectile::AXYZProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetCollisionProfileName("NoCollision");
}

void AXYZProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AXYZProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!HasAuthority())
	{
		MoveToTarget(DeltaTime);
	}
}

void AXYZProjectile::MoveToTarget(float DeltaTime)
{
	FVector StartLocation = GetActorLocation();
	FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
	FVector NewLocation = StartLocation + Direction * ProjectileSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AXYZProjectile::Process(float DeltaTime)
{
	TimeAlive += DeltaTime;
	if(TargetActor)
	{
		TargetLocation = TargetActor->GetActorLocation();
	}
	if (FVector::Dist(GetActorLocation(), TargetLocation) < DestroyDistance || TimeAlive >= MaxAliveTime)
	{
		bDestroyFlag = true;
		return;
	}
	
	MoveToTarget(DeltaTime);
}

void AXYZProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZProjectile, TargetLocation);
}

