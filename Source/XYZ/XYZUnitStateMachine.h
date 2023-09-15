// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZUnitState.h"
#include "XYZUnitStateMachine.generated.h"
/**
 * 
 */
UCLASS()
class XYZ_API UXYZUnitStateMachine : public UObject
{
	GENERATED_BODY()

public:
	EXYZUnitState CurrentState;
	EXYZUnitState PrevState;

	void SetState(EXYZUnitState State) {
		switch (State) {
		case EXYZUnitState::IDLE:
			break;
		case EXYZUnitState::MOVING:
			break;
		case EXYZUnitState::ATTACK_MOVING:
			break;
		case EXYZUnitState::ATTACKING:
			break;
		}
		PrevState = CurrentState;
		CurrentState = State;
	}
};
