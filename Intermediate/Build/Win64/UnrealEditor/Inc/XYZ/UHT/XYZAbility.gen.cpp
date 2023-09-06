// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZAbility.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZAbility() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZAbility();
	XYZ_API UClass* Z_Construct_UClass_UXYZAbility_NoRegister();
// End Cross Module References
	void UXYZAbility::StaticRegisterNativesUXYZAbility()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZAbility);
	UClass* Z_Construct_UClass_UXYZAbility_NoRegister()
	{
		return UXYZAbility::StaticClass();
	}
	struct Z_Construct_UClass_UXYZAbility_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ID;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Cooldown_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Cooldown;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZAbility_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAbility_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Represents a basic ability in the XYZ game.\n */" },
		{ "IncludePath", "XYZAbility.h" },
		{ "ModuleRelativePath", "XYZAbility.h" },
		{ "ToolTip", "Represents a basic ability in the XYZ game." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAbility_Statics::NewProp_ID_MetaData[] = {
		{ "Category", "Ability" },
		{ "Comment", "/** The unique ID of the ability. */" },
		{ "ModuleRelativePath", "XYZAbility.h" },
		{ "ToolTip", "The unique ID of the ability." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UXYZAbility_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAbility, ID), METADATA_PARAMS(Z_Construct_UClass_UXYZAbility_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAbility_Statics::NewProp_ID_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAbility_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Ability" },
		{ "Comment", "/** The name of the ability. */" },
		{ "ModuleRelativePath", "XYZAbility.h" },
		{ "ToolTip", "The name of the ability." },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UXYZAbility_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAbility, Name), METADATA_PARAMS(Z_Construct_UClass_UXYZAbility_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAbility_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAbility_Statics::NewProp_Cooldown_MetaData[] = {
		{ "Category", "Ability" },
		{ "Comment", "/** The cooldown duration of the ability in seconds. */" },
		{ "ModuleRelativePath", "XYZAbility.h" },
		{ "ToolTip", "The cooldown duration of the ability in seconds." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UXYZAbility_Statics::NewProp_Cooldown = { "Cooldown", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAbility, Cooldown), METADATA_PARAMS(Z_Construct_UClass_UXYZAbility_Statics::NewProp_Cooldown_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAbility_Statics::NewProp_Cooldown_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UXYZAbility_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAbility_Statics::NewProp_ID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAbility_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAbility_Statics::NewProp_Cooldown,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZAbility_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZAbility>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZAbility_Statics::ClassParams = {
		&UXYZAbility::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UXYZAbility_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAbility_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZAbility_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAbility_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZAbility()
	{
		if (!Z_Registration_Info_UClass_UXYZAbility.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZAbility.OuterSingleton, Z_Construct_UClass_UXYZAbility_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZAbility.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZAbility>()
	{
		return UXYZAbility::StaticClass();
	}
	UXYZAbility::UXYZAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZAbility);
	UXYZAbility::~UXYZAbility() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAbility_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAbility_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZAbility, UXYZAbility::StaticClass, TEXT("UXYZAbility"), &Z_Registration_Info_UClass_UXYZAbility, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZAbility), 3020674545U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAbility_h_2200430552(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAbility_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAbility_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
