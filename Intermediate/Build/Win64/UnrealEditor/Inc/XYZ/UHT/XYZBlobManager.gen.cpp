// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZBlobManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZBlobManager() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlob_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlobManager();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlobManager_NoRegister();
// End Cross Module References
	void UXYZBlobManager::StaticRegisterNativesUXYZBlobManager()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZBlobManager);
	UClass* Z_Construct_UClass_UXYZBlobManager_NoRegister()
	{
		return UXYZBlobManager::StaticClass();
	}
	struct Z_Construct_UClass_UXYZBlobManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ActiveBlobs_ValueProp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ActiveBlobs_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActiveBlobs_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ActiveBlobs;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZBlobManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZBlobManager_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZBlobManager.h" },
		{ "ModuleRelativePath", "XYZBlobManager.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_ValueProp = { "ActiveBlobs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, Z_Construct_UClass_UXYZBlob_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_Key_KeyProp = { "ActiveBlobs_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_MetaData[] = {
		{ "ModuleRelativePath", "XYZBlobManager.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs = { "ActiveBlobs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZBlobManager, ActiveBlobs), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UXYZBlobManager_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZBlobManager_Statics::NewProp_ActiveBlobs,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZBlobManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZBlobManager>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZBlobManager_Statics::ClassParams = {
		&UXYZBlobManager::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UXYZBlobManager_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UXYZBlobManager_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZBlobManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZBlobManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZBlobManager()
	{
		if (!Z_Registration_Info_UClass_UXYZBlobManager.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZBlobManager.OuterSingleton, Z_Construct_UClass_UXYZBlobManager_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZBlobManager.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZBlobManager>()
	{
		return UXYZBlobManager::StaticClass();
	}
	UXYZBlobManager::UXYZBlobManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZBlobManager);
	UXYZBlobManager::~UXYZBlobManager() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobManager_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobManager_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZBlobManager, UXYZBlobManager::StaticClass, TEXT("UXYZBlobManager"), &Z_Registration_Info_UClass_UXYZBlobManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZBlobManager), 4101168796U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobManager_h_1676546655(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobManager_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
