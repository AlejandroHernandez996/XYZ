// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZAIController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZAIController() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_AAIController();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZAIController();
	XYZ_API UClass* Z_Construct_UClass_AXYZAIController_NoRegister();
// End Cross Module References
	void AXYZAIController::StaticRegisterNativesAXYZAIController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXYZAIController);
	UClass* Z_Construct_UClass_AXYZAIController_NoRegister()
	{
		return AXYZAIController::StaticClass();
	}
	struct Z_Construct_UClass_AXYZAIController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZAIController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAIController,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZAIController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "XYZAIController.h" },
		{ "ModuleRelativePath", "XYZAIController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXYZAIController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXYZAIController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXYZAIController_Statics::ClassParams = {
		&AXYZAIController::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AXYZAIController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZAIController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXYZAIController()
	{
		if (!Z_Registration_Info_UClass_AXYZAIController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXYZAIController.OuterSingleton, Z_Construct_UClass_AXYZAIController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXYZAIController.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<AXYZAIController>()
	{
		return AXYZAIController::StaticClass();
	}
	AXYZAIController::AXYZAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXYZAIController);
	AXYZAIController::~AXYZAIController() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAIController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAIController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXYZAIController, AXYZAIController::StaticClass, TEXT("AXYZAIController"), &Z_Registration_Info_UClass_AXYZAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZAIController), 2554113861U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAIController_h_2221991065(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAIController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAIController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
