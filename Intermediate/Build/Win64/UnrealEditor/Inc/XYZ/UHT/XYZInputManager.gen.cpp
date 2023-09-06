// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZInputManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZInputManager() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZInputManager();
	XYZ_API UClass* Z_Construct_UClass_UXYZInputManager_NoRegister();
// End Cross Module References
	void UXYZInputManager::StaticRegisterNativesUXYZInputManager()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZInputManager);
	UClass* Z_Construct_UClass_UXYZInputManager_NoRegister()
	{
		return UXYZInputManager::StaticClass();
	}
	struct Z_Construct_UClass_UXYZInputManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZInputManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZInputManager_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZInputManager.h" },
		{ "ModuleRelativePath", "XYZInputManager.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZInputManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZInputManager>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZInputManager_Statics::ClassParams = {
		&UXYZInputManager::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZInputManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZInputManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZInputManager()
	{
		if (!Z_Registration_Info_UClass_UXYZInputManager.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZInputManager.OuterSingleton, Z_Construct_UClass_UXYZInputManager_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZInputManager.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZInputManager>()
	{
		return UXYZInputManager::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZInputManager);
	UXYZInputManager::~UXYZInputManager() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputManager_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputManager_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZInputManager, UXYZInputManager::StaticClass, TEXT("UXYZInputManager"), &Z_Registration_Info_UClass_UXYZInputManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZInputManager), 3160927565U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputManager_h_278755971(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputManager_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
