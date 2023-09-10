// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZInputType.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZInputType() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZInputType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXYZInputType;
	static UEnum* EXYZInputType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EXYZInputType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EXYZInputType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_XYZ_EXYZInputType, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("EXYZInputType"));
		}
		return Z_Registration_Info_UEnum_EXYZInputType.OuterSingleton;
	}
	template<> XYZ_API UEnum* StaticEnum<EXYZInputType>()
	{
		return EXYZInputType_StaticEnum();
	}
	struct Z_Construct_UEnum_XYZ_EXYZInputType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_XYZ_EXYZInputType_Statics::Enumerators[] = {
		{ "EXYZInputType::PRIMARY_INPUT", (int64)EXYZInputType::PRIMARY_INPUT },
		{ "EXYZInputType::SECONDARY_INPUT", (int64)EXYZInputType::SECONDARY_INPUT },
		{ "EXYZInputType::ATTACK_MOVE", (int64)EXYZInputType::ATTACK_MOVE },
		{ "EXYZInputType::PRIMARY_MOD", (int64)EXYZInputType::PRIMARY_MOD },
		{ "EXYZInputType::SECONDARY_MOD", (int64)EXYZInputType::SECONDARY_MOD },
		{ "EXYZInputType::NONE", (int64)EXYZInputType::NONE },
		{ "EXYZInputType::CLEAR", (int64)EXYZInputType::CLEAR },
		{ "EXYZInputType::STOP", (int64)EXYZInputType::STOP },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_XYZ_EXYZInputType_Statics::Enum_MetaDataParams[] = {
		{ "ATTACK_MOVE.Name", "EXYZInputType::ATTACK_MOVE" },
		{ "BlueprintType", "true" },
		{ "CLEAR.Name", "EXYZInputType::CLEAR" },
		{ "ModuleRelativePath", "XYZInputType.h" },
		{ "NONE.Name", "EXYZInputType::NONE" },
		{ "PRIMARY_INPUT.Name", "EXYZInputType::PRIMARY_INPUT" },
		{ "PRIMARY_MOD.Name", "EXYZInputType::PRIMARY_MOD" },
		{ "SECONDARY_INPUT.Name", "EXYZInputType::SECONDARY_INPUT" },
		{ "SECONDARY_MOD.Name", "EXYZInputType::SECONDARY_MOD" },
		{ "STOP.Name", "EXYZInputType::STOP" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_XYZ_EXYZInputType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		"EXYZInputType",
		"EXYZInputType",
		Z_Construct_UEnum_XYZ_EXYZInputType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZInputType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_XYZ_EXYZInputType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZInputType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_XYZ_EXYZInputType()
	{
		if (!Z_Registration_Info_UEnum_EXYZInputType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXYZInputType.InnerSingleton, Z_Construct_UEnum_XYZ_EXYZInputType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EXYZInputType.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputType_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputType_h_Statics::EnumInfo[] = {
		{ EXYZInputType_StaticEnum, TEXT("EXYZInputType"), &Z_Registration_Info_UEnum_EXYZInputType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1490979030U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputType_h_1070138806(TEXT("/Script/XYZ"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputType_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputType_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
