// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZInputType.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef XYZ_XYZInputType_generated_h
#error "XYZInputType.generated.h already included, missing '#pragma once' in XYZInputType.h"
#endif
#define XYZ_XYZInputType_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputType_h


#define FOREACH_ENUM_EXYZINPUTTYPE(op) \
	op(EXYZInputType::PRIMARY_INPUT) \
	op(EXYZInputType::SECONDARY_INPUT) \
	op(EXYZInputType::ATTACK_MOVE) \
	op(EXYZInputType::PRIMARY_MOD) \
	op(EXYZInputType::SECONDARY_MOD) \
	op(EXYZInputType::NONE) \
	op(EXYZInputType::STOP) 

enum class EXYZInputType : uint8;
template<> struct TIsUEnumClass<EXYZInputType> { enum { Value = true }; };
template<> XYZ_API UEnum* StaticEnum<EXYZInputType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
