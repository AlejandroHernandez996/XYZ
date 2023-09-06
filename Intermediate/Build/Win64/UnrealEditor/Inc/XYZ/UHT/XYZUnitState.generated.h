// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZUnitState.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef XYZ_XYZUnitState_generated_h
#error "XYZUnitState.generated.h already included, missing '#pragma once' in XYZUnitState.h"
#endif
#define XYZ_XYZUnitState_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnitState_h


#define FOREACH_ENUM_EXYZUNITSTATE(op) \
	op(EXYZUnitState::IDLE) \
	op(EXYZUnitState::ATTACK) \
	op(EXYZUnitState::MOVE) 

enum class EXYZUnitState : uint8;
template<> struct TIsUEnumClass<EXYZUnitState> { enum { Value = true }; };
template<> XYZ_API UEnum* StaticEnum<EXYZUnitState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
