// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZDecalType.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef XYZ_XYZDecalType_generated_h
#error "XYZDecalType.generated.h already included, missing '#pragma once' in XYZDecalType.h"
#endif
#define XYZ_XYZDecalType_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZDecalType_h


#define FOREACH_ENUM_EXYZDECALTYPE(op) \
	op(EXYZDecalType::FRIENDLY) \
	op(EXYZDecalType::ENEMY) \
	op(EXYZDecalType::NEUTRAL) 

enum class EXYZDecalType : uint8;
template<> struct TIsUEnumClass<EXYZDecalType> { enum { Value = true }; };
template<> XYZ_API UEnum* StaticEnum<EXYZDecalType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
