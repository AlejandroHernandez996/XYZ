// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZSelectionStructure.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZSelectionStructure() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZSelectionStructure();
	XYZ_API UClass* Z_Construct_UClass_UXYZSelectionStructure_NoRegister();
// End Cross Module References
	void UXYZSelectionStructure::StaticRegisterNativesUXYZSelectionStructure()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZSelectionStructure);
	UClass* Z_Construct_UClass_UXYZSelectionStructure_NoRegister()
	{
		return UXYZSelectionStructure::StaticClass();
	}
	struct Z_Construct_UClass_UXYZSelectionStructure_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZSelectionStructure_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZSelectionStructure_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZSelectionStructure.h" },
		{ "ModuleRelativePath", "XYZSelectionStructure.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZSelectionStructure_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZSelectionStructure>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZSelectionStructure_Statics::ClassParams = {
		&UXYZSelectionStructure::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UXYZSelectionStructure_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZSelectionStructure_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZSelectionStructure()
	{
		if (!Z_Registration_Info_UClass_UXYZSelectionStructure.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZSelectionStructure.OuterSingleton, Z_Construct_UClass_UXYZSelectionStructure_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZSelectionStructure.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZSelectionStructure>()
	{
		return UXYZSelectionStructure::StaticClass();
	}
	UXYZSelectionStructure::UXYZSelectionStructure(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZSelectionStructure);
	UXYZSelectionStructure::~UXYZSelectionStructure() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZSelectionStructure, UXYZSelectionStructure::StaticClass, TEXT("UXYZSelectionStructure"), &Z_Registration_Info_UClass_UXYZSelectionStructure, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZSelectionStructure), 1837231812U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_50476547(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
