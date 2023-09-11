// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZEvadeAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZEvadeAction() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZEvadeAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZEvadeAction_NoRegister();
// End Cross Module References
	void UXYZEvadeAction::StaticRegisterNativesUXYZEvadeAction()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZEvadeAction);
	UClass* Z_Construct_UClass_UXYZEvadeAction_NoRegister()
	{
		return UXYZEvadeAction::StaticClass();
	}
	struct Z_Construct_UClass_UXYZEvadeAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZEvadeAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UXYZAction,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZEvadeAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "XYZEvadeAction.h" },
		{ "ModuleRelativePath", "XYZEvadeAction.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZEvadeAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZEvadeAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZEvadeAction_Statics::ClassParams = {
		&UXYZEvadeAction::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UXYZEvadeAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZEvadeAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZEvadeAction()
	{
		if (!Z_Registration_Info_UClass_UXYZEvadeAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZEvadeAction.OuterSingleton, Z_Construct_UClass_UXYZEvadeAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZEvadeAction.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZEvadeAction>()
	{
		return UXYZEvadeAction::StaticClass();
	}
	UXYZEvadeAction::UXYZEvadeAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZEvadeAction);
	UXYZEvadeAction::~UXYZEvadeAction() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZEvadeAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZEvadeAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZEvadeAction, UXYZEvadeAction::StaticClass, TEXT("UXYZEvadeAction"), &Z_Registration_Info_UClass_UXYZEvadeAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZEvadeAction), 273087615U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZEvadeAction_h_2838173010(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZEvadeAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZEvadeAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
