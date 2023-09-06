// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZGameMode();
	XYZ_API UClass* Z_Construct_UClass_AXYZGameMode_NoRegister();
// End Cross Module References
	void AXYZGameMode::StaticRegisterNativesAXYZGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXYZGameMode);
	UClass* Z_Construct_UClass_AXYZGameMode_NoRegister()
	{
		return AXYZGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AXYZGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "XYZGameMode.h" },
		{ "ModuleRelativePath", "XYZGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXYZGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXYZGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXYZGameMode_Statics::ClassParams = {
		&AXYZGameMode::StaticClass,
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
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AXYZGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXYZGameMode()
	{
		if (!Z_Registration_Info_UClass_AXYZGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXYZGameMode.OuterSingleton, Z_Construct_UClass_AXYZGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXYZGameMode.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<AXYZGameMode>()
	{
		return AXYZGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXYZGameMode);
	AXYZGameMode::~AXYZGameMode() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXYZGameMode, AXYZGameMode::StaticClass, TEXT("AXYZGameMode"), &Z_Registration_Info_UClass_AXYZGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZGameMode), 3155269808U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameMode_h_1696554146(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
