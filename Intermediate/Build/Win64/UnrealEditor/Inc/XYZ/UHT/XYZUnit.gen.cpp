// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZUnit.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZUnit() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor();
	XYZ_API UClass* Z_Construct_UClass_AXYZUnit();
	XYZ_API UClass* Z_Construct_UClass_AXYZUnit_NoRegister();
// End Cross Module References
	void AXYZUnit::StaticRegisterNativesAXYZUnit()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXYZUnit);
	UClass* Z_Construct_UClass_AXYZUnit_NoRegister()
	{
		return AXYZUnit::StaticClass();
	}
	struct Z_Construct_UClass_AXYZUnit_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZUnit_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AXYZActor,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZUnit_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "XYZUnit.h" },
		{ "ModuleRelativePath", "XYZUnit.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXYZUnit_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXYZUnit>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXYZUnit_Statics::ClassParams = {
		&AXYZUnit::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AXYZUnit_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZUnit_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXYZUnit()
	{
		if (!Z_Registration_Info_UClass_AXYZUnit.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXYZUnit.OuterSingleton, Z_Construct_UClass_AXYZUnit_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXYZUnit.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<AXYZUnit>()
	{
		return AXYZUnit::StaticClass();
	}
	AXYZUnit::AXYZUnit() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXYZUnit);
	AXYZUnit::~AXYZUnit() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnit_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnit_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXYZUnit, AXYZUnit::StaticClass, TEXT("AXYZUnit"), &Z_Registration_Info_UClass_AXYZUnit, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZUnit), 3583420108U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnit_h_1329516687(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnit_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnit_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
