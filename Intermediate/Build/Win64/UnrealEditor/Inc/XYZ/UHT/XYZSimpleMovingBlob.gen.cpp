// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZSimpleMovingBlob.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZSimpleMovingBlob() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlob();
	XYZ_API UClass* Z_Construct_UClass_UXYZSimpleMovingBlob();
	XYZ_API UClass* Z_Construct_UClass_UXYZSimpleMovingBlob_NoRegister();
	XYZ_API UScriptStruct* Z_Construct_UScriptStruct_FAgentPack();
// End Cross Module References
	void UXYZSimpleMovingBlob::StaticRegisterNativesUXYZSimpleMovingBlob()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZSimpleMovingBlob);
	UClass* Z_Construct_UClass_UXYZSimpleMovingBlob_NoRegister()
	{
		return UXYZSimpleMovingBlob::StaticClass();
	}
	struct Z_Construct_UClass_UXYZSimpleMovingBlob_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UXYZBlob,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZSimpleMovingBlob.h" },
		{ "ModuleRelativePath", "XYZSimpleMovingBlob.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZSimpleMovingBlob>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::ClassParams = {
		&UXYZSimpleMovingBlob::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZSimpleMovingBlob()
	{
		if (!Z_Registration_Info_UClass_UXYZSimpleMovingBlob.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZSimpleMovingBlob.OuterSingleton, Z_Construct_UClass_UXYZSimpleMovingBlob_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZSimpleMovingBlob.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZSimpleMovingBlob>()
	{
		return UXYZSimpleMovingBlob::StaticClass();
	}
	UXYZSimpleMovingBlob::UXYZSimpleMovingBlob(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZSimpleMovingBlob);
	UXYZSimpleMovingBlob::~UXYZSimpleMovingBlob() {}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_AgentPack;
class UScriptStruct* FAgentPack::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_AgentPack.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_AgentPack.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAgentPack, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("AgentPack"));
	}
	return Z_Registration_Info_UScriptStruct_AgentPack.OuterSingleton;
}
template<> XYZ_API UScriptStruct* StaticStruct<FAgentPack>()
{
	return FAgentPack::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FAgentPack_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAgentPack_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZSimpleMovingBlob.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAgentPack_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAgentPack>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAgentPack_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		&NewStructOps,
		"AgentPack",
		sizeof(FAgentPack),
		alignof(FAgentPack),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAgentPack_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAgentPack_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAgentPack()
	{
		if (!Z_Registration_Info_UScriptStruct_AgentPack.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_AgentPack.InnerSingleton, Z_Construct_UScriptStruct_FAgentPack_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_AgentPack.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics::ScriptStructInfo[] = {
		{ FAgentPack::StaticStruct, Z_Construct_UScriptStruct_FAgentPack_Statics::NewStructOps, TEXT("AgentPack"), &Z_Registration_Info_UScriptStruct_AgentPack, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAgentPack), 232236319U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZSimpleMovingBlob, UXYZSimpleMovingBlob::StaticClass, TEXT("UXYZSimpleMovingBlob"), &Z_Registration_Info_UClass_UXYZSimpleMovingBlob, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZSimpleMovingBlob), 1202389894U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_2363694400(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSimpleMovingBlob_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
