// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZ_init() {}
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionIdsEvent__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_XYZ;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_XYZ()
	{
		if (!Z_Registration_Info_UPackage__Script_XYZ.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_XYZ_SelectionIdsEvent__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/XYZ",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x8861E7F0,
				0x32441284,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_XYZ.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_XYZ.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_XYZ(Z_Construct_UPackage__Script_XYZ, TEXT("/Script/XYZ"), Z_Registration_Info_UPackage__Script_XYZ, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x8861E7F0, 0x32441284));
PRAGMA_ENABLE_DEPRECATION_WARNINGS