// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZBlob.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZBlob() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlob();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlob_NoRegister();
// End Cross Module References
	void UXYZBlob::StaticRegisterNativesUXYZBlob()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZBlob);
	UClass* Z_Construct_UClass_UXYZBlob_NoRegister()
	{
		return UXYZBlob::StaticClass();
	}
	struct Z_Construct_UClass_UXYZBlob_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZBlob_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZBlob_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZBlob.h" },
		{ "ModuleRelativePath", "XYZBlob.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZBlob_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZBlob>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZBlob_Statics::ClassParams = {
		&UXYZBlob::StaticClass,
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
		0x001000A1u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZBlob_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZBlob_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZBlob()
	{
		if (!Z_Registration_Info_UClass_UXYZBlob.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZBlob.OuterSingleton, Z_Construct_UClass_UXYZBlob_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZBlob.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZBlob>()
	{
		return UXYZBlob::StaticClass();
	}
	UXYZBlob::UXYZBlob(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZBlob);
	UXYZBlob::~UXYZBlob() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlob_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlob_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZBlob, UXYZBlob::StaticClass, TEXT("UXYZBlob"), &Z_Registration_Info_UClass_UXYZBlob, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZBlob), 370303725U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlob_h_3368790832(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlob_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlob_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
