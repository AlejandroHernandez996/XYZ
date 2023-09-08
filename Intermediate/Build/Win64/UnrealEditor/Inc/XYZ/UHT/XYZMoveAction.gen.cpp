// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZMoveAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZMoveAction() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZMoveAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZMoveAction_NoRegister();
// End Cross Module References
	void UXYZMoveAction::StaticRegisterNativesUXYZMoveAction()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZMoveAction);
	UClass* Z_Construct_UClass_UXYZMoveAction_NoRegister()
	{
		return UXYZMoveAction::StaticClass();
	}
	struct Z_Construct_UClass_UXYZMoveAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetLocationThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_TargetLocationThreshold;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZMoveAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UXYZAction,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZMoveAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "XYZMoveAction.h" },
		{ "ModuleRelativePath", "XYZMoveAction.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZMoveAction_Statics::NewProp_TargetLocationThreshold_MetaData[] = {
		{ "Category", "Move" },
		{ "ModuleRelativePath", "XYZMoveAction.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UXYZMoveAction_Statics::NewProp_TargetLocationThreshold = { "TargetLocationThreshold", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZMoveAction, TargetLocationThreshold), METADATA_PARAMS(Z_Construct_UClass_UXYZMoveAction_Statics::NewProp_TargetLocationThreshold_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZMoveAction_Statics::NewProp_TargetLocationThreshold_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UXYZMoveAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZMoveAction_Statics::NewProp_TargetLocationThreshold,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZMoveAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZMoveAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZMoveAction_Statics::ClassParams = {
		&UXYZMoveAction::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UXYZMoveAction_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UXYZMoveAction_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZMoveAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZMoveAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZMoveAction()
	{
		if (!Z_Registration_Info_UClass_UXYZMoveAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZMoveAction.OuterSingleton, Z_Construct_UClass_UXYZMoveAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZMoveAction.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZMoveAction>()
	{
		return UXYZMoveAction::StaticClass();
	}
	UXYZMoveAction::UXYZMoveAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZMoveAction);
	UXYZMoveAction::~UXYZMoveAction() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZMoveAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZMoveAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZMoveAction, UXYZMoveAction::StaticClass, TEXT("UXYZMoveAction"), &Z_Registration_Info_UClass_UXYZMoveAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZMoveAction), 3503851778U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZMoveAction_h_3131231842(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZMoveAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZMoveAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
