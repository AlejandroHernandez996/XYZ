// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZAttackAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZAttackAction() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZAttackAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZAttackAction_NoRegister();
// End Cross Module References
	void UXYZAttackAction::StaticRegisterNativesUXYZAttackAction()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZAttackAction);
	UClass* Z_Construct_UClass_UXYZAttackAction_NoRegister()
	{
		return UXYZAttackAction::StaticClass();
	}
	struct Z_Construct_UClass_UXYZAttackAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetLocationThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_TargetLocationThreshold;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIgnoreAllies_MetaData[];
#endif
		static void NewProp_bIgnoreAllies_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIgnoreAllies;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZAttackAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UXYZAction,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAttackAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "XYZAttackAction.h" },
		{ "ModuleRelativePath", "XYZAttackAction.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_TargetLocationThreshold_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "XYZAttackAction.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_TargetLocationThreshold = { "TargetLocationThreshold", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAttackAction, TargetLocationThreshold), METADATA_PARAMS(Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_TargetLocationThreshold_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_TargetLocationThreshold_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "XYZAttackAction.h" },
	};
#endif
	void Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies_SetBit(void* Obj)
	{
		((UXYZAttackAction*)Obj)->bIgnoreAllies = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies = { "bIgnoreAllies", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UXYZAttackAction), &Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies_SetBit, METADATA_PARAMS(Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UXYZAttackAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_TargetLocationThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAttackAction_Statics::NewProp_bIgnoreAllies,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZAttackAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZAttackAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZAttackAction_Statics::ClassParams = {
		&UXYZAttackAction::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UXYZAttackAction_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAttackAction_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZAttackAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAttackAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZAttackAction()
	{
		if (!Z_Registration_Info_UClass_UXYZAttackAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZAttackAction.OuterSingleton, Z_Construct_UClass_UXYZAttackAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZAttackAction.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZAttackAction>()
	{
		return UXYZAttackAction::StaticClass();
	}
	UXYZAttackAction::UXYZAttackAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZAttackAction);
	UXYZAttackAction::~UXYZAttackAction() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAttackAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAttackAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZAttackAction, UXYZAttackAction::StaticClass, TEXT("UXYZAttackAction"), &Z_Registration_Info_UClass_UXYZAttackAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZAttackAction), 1605916965U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAttackAction_h_1185619836(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAttackAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAttackAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
