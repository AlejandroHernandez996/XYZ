// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZActionState.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef XYZ_XYZActionState_generated_h
#error "XYZActionState.generated.h already included, missing '#pragma once' in XYZActionState.h"
#endif
#define XYZ_XYZActionState_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionState_h


#define FOREACH_ENUM_EXYZACTIONSTATE(op) \
	op(EXYZActionState::QUEUED) \
	op(EXYZActionState::IN_PROGRESS) \
	op(EXYZActionState::COMPLETE) \
	op(EXYZActionState::CANCELLED) 

enum class EXYZActionState : uint8;
template<> struct TIsUEnumClass<EXYZActionState> { enum { Value = true }; };
template<> XYZ_API UEnum* StaticEnum<EXYZActionState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
