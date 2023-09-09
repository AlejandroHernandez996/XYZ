// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZStopAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZStopAction() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZStopAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZStopAction_NoRegister();
// End Cross Module References
	void UXYZStopAction::StaticRegisterNativesUXYZStopAction()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZStopAction);
	UClass* Z_Construct_UClass_UXYZStopAction_NoRegister()
	{
		return UXYZStopAction::StaticClass();
	}
	struct Z_Construct_UClass_UXYZStopAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZStopAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UXYZAction,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZStopAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "XYZStopAction.h" },
		{ "ModuleRelativePath", "XYZStopAction.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZStopAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZStopAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZStopAction_Statics::ClassParams = {
		&UXYZStopAction::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UXYZStopAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZStopAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZStopAction()
	{
		if (!Z_Registration_Info_UClass_UXYZStopAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZStopAction.OuterSingleton, Z_Construct_UClass_UXYZStopAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZStopAction.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZStopAction>()
	{
		return UXYZStopAction::StaticClass();
	}
	UXYZStopAction::UXYZStopAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZStopAction);
	UXYZStopAction::~UXYZStopAction() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZStopAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZStopAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZStopAction, UXYZStopAction::StaticClass, TEXT("UXYZStopAction"), &Z_Registration_Info_UClass_UXYZStopAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZStopAction), 2048240188U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZStopAction_h_2307513470(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZStopAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZStopAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
