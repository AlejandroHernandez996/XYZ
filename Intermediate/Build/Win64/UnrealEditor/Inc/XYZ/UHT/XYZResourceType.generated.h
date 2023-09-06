// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZResourceType.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef XYZ_XYZResourceType_generated_h
#error "XYZResourceType.generated.h already included, missing '#pragma once' in XYZResourceType.h"
#endif
#define XYZ_XYZResourceType_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZResourceType_h


#define FOREACH_ENUM_EXYZRESOURCETYPE(op) \
	op(EXYZResourceType::MINERAL) \
	op(EXYZResourceType::GAS) 

enum class EXYZResourceType : uint8;
template<> struct TIsUEnumClass<EXYZResourceType> { enum { Value = true }; };
template<> XYZ_API UEnum* StaticEnum<EXYZResourceType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
