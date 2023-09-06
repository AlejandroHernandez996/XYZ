// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZ_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_XYZ;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_XYZ()
	{
		if (!Z_Registration_Info_UPackage__Script_XYZ.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/XYZ",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x3E68DE46,
				0x6321200F,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_XYZ.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_XYZ.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_XYZ(Z_Construct_UPackage__Script_XYZ, TEXT("/Script/XYZ"), Z_Registration_Info_UPackage__Script_XYZ, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x3E68DE46, 0x6321200F));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
