// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZResourceActor.h"

#include "Net/UnrealNetwork.h"

void AXYZResourceActor::Process(float DeltaSeconds)
{
	Super::Process(DeltaSeconds);
	CurrentWorkers = Workers.Num();

	TArray<AXYZWorker*> WorkerArray;
	Workers.GenerateKeyArray(WorkerArray);

	for(AXYZWorker* Worker : WorkerArray)
	{
		if(!Worker || (Worker->State != EXYZUnitState::GATHERING && Worker->State != EXYZUnitState::MINING && Worker->State != EXYZUnitState::RETURNING))
		{
			RemoveWorker(Worker);
		}
		if(Worker && Worker->TargetActor != this)
		{
			RemoveWorker(Worker);
		}
	}
}

void AXYZResourceActor::AddWorker(AXYZWorker* Worker)
{
	const bool bCanWork = Workers.Num() < RESOURCE_CAPACITY;
	Workers.Add(Worker, bCanWork);
}

void AXYZResourceActor::RemoveWorker(const AXYZWorker* Worker)
{
	if(Workers.Contains(Worker)){
		if(Worker && Worker->TargetActor == this)
		{
			Worker->TargetActor = nullptr;
		}
		Workers.Remove(Worker);
	}
}

void AXYZResourceActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZResourceActor, CurrentWorkers);
}
