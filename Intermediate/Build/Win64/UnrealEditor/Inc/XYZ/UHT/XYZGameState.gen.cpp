// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZGameState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZGameState() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameStateBase();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_AXYZGameState();
	XYZ_API UClass* Z_Construct_UClass_AXYZGameState_NoRegister();
// End Cross Module References
	void AXYZGameState::StaticRegisterNativesAXYZGameState()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXYZGameState);
	UClass* Z_Construct_UClass_AXYZGameState_NoRegister()
	{
		return AXYZGameState::StaticClass();
	}
	struct Z_Construct_UClass_AXYZGameState_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_AllActors_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AllActors_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_AllActors;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorsByUID_ValueProp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ActorsByUID_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActorsByUID_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ActorsByUID;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZGameState_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameStateBase,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZGameState_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "XYZGameState.h" },
		{ "ModuleRelativePath", "XYZGameState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors_Inner = { "AllActors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors_MetaData[] = {
		{ "ModuleRelativePath", "XYZGameState.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors = { "AllActors", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZGameState, AllActors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_ValueProp = { "ActorsByUID", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_Key_KeyProp = { "ActorsByUID_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_MetaData[] = {
		{ "Category", "XYZGameState" },
		{ "ModuleRelativePath", "XYZGameState.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID = { "ActorsByUID", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZGameState, ActorsByUID), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AXYZGameState_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZGameState_Statics::NewProp_AllActors,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZGameState_Statics::NewProp_ActorsByUID,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXYZGameState_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXYZGameState>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXYZGameState_Statics::ClassParams = {
		&AXYZGameState::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AXYZGameState_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AXYZGameState_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AXYZGameState_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZGameState_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXYZGameState()
	{
		if (!Z_Registration_Info_UClass_AXYZGameState.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXYZGameState.OuterSingleton, Z_Construct_UClass_AXYZGameState_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXYZGameState.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<AXYZGameState>()
	{
		return AXYZGameState::StaticClass();
	}
	AXYZGameState::AXYZGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXYZGameState);
	AXYZGameState::~AXYZGameState() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameState_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameState_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXYZGameState, AXYZGameState::StaticClass, TEXT("AXYZGameState"), &Z_Registration_Info_UClass_AXYZGameState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZGameState), 85794343U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameState_h_4169200154(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZGameState_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
