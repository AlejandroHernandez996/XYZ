// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZActor() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZAbility_NoRegister();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZFactionType();
// End Cross Module References
	void AXYZActor::StaticRegisterNativesAXYZActor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXYZActor);
	UClass* Z_Construct_UClass_AXYZActor_NoRegister()
	{
		return AXYZActor::StaticClass();
	}
	struct Z_Construct_UClass_AXYZActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActorId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ActorId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UActorId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_UActorId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TeamId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TeamId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Faction_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Faction_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Faction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Health;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHealth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BaseArmor_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BaseArmor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackDamage_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AttackDamage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackRate_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackRate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackRange_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackRange;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Abilities_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Abilities_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Abilities;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZActor.h" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_ActorId_MetaData[] = {
		{ "Category", "Info" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_ActorId = { "ActorId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, ActorId), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_ActorId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_ActorId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_UActorId_MetaData[] = {
		{ "Category", "Info" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_UActorId = { "UActorId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, UActorId), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_UActorId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_UActorId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_TeamId_MetaData[] = {
		{ "Category", "Info" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_TeamId = { "TeamId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, TeamId), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_TeamId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_TeamId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "Info" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, DisplayName), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_DisplayName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_DisplayName_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction_MetaData[] = {
		{ "Category", "Info" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction = { "Faction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, Faction), Z_Construct_UEnum_XYZ_EXYZFactionType, METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction_MetaData)) }; // 3193192588
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_Health_MetaData[] = {
		{ "Category", "Stats" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_Health = { "Health", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, Health), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_Health_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_Health_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Stats" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, MaxHealth), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_MaxHealth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_MaxHealth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_MoveSpeed_MetaData[] = {
		{ "Category", "Stats" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_MoveSpeed = { "MoveSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, MoveSpeed), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_MoveSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_MoveSpeed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_BaseArmor_MetaData[] = {
		{ "Category", "Stats" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_BaseArmor = { "BaseArmor", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, BaseArmor), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_BaseArmor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_BaseArmor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackDamage_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackDamage = { "AttackDamage", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, AttackDamage), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackDamage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackDamage_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackSpeed_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackSpeed = { "AttackSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, AttackSpeed), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackSpeed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRate_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRate = { "AttackRate", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, AttackRate), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRate_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRange_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRange = { "AttackRange", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, AttackRange), METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRange_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRange_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities_Inner = { "Abilities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UXYZAbility_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities_MetaData[] = {
		{ "Category", "Abilities" },
		{ "ModuleRelativePath", "XYZActor.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities = { "Abilities", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZActor, Abilities), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AXYZActor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_ActorId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_UActorId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_TeamId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_DisplayName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_Faction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_Health,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_MaxHealth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_MoveSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_BaseArmor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackDamage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_AttackRange,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZActor_Statics::NewProp_Abilities,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXYZActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXYZActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXYZActor_Statics::ClassParams = {
		&AXYZActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AXYZActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AXYZActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXYZActor()
	{
		if (!Z_Registration_Info_UClass_AXYZActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXYZActor.OuterSingleton, Z_Construct_UClass_AXYZActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXYZActor.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<AXYZActor>()
	{
		return AXYZActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXYZActor);
	AXYZActor::~AXYZActor() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXYZActor, AXYZActor::StaticClass, TEXT("AXYZActor"), &Z_Registration_Info_UClass_AXYZActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZActor), 2013198938U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_1360864314(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
