// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZDecalType.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZDecalType() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZDecalType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXYZDecalType;
	static UEnum* EXYZDecalType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EXYZDecalType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EXYZDecalType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_XYZ_EXYZDecalType, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("EXYZDecalType"));
		}
		return Z_Registration_Info_UEnum_EXYZDecalType.OuterSingleton;
	}
	template<> XYZ_API UEnum* StaticEnum<EXYZDecalType>()
	{
		return EXYZDecalType_StaticEnum();
	}
	struct Z_Construct_UEnum_XYZ_EXYZDecalType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::Enumerators[] = {
		{ "EXYZDecalType::FRIENDLY", (int64)EXYZDecalType::FRIENDLY },
		{ "EXYZDecalType::ENEMY", (int64)EXYZDecalType::ENEMY },
		{ "EXYZDecalType::NEUTRAL", (int64)EXYZDecalType::NEUTRAL },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ENEMY.Name", "EXYZDecalType::ENEMY" },
		{ "FRIENDLY.Name", "EXYZDecalType::FRIENDLY" },
		{ "ModuleRelativePath", "XYZDecalType.h" },
		{ "NEUTRAL.Name", "EXYZDecalType::NEUTRAL" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		"EXYZDecalType",
		"EXYZDecalType",
		Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_XYZ_EXYZDecalType()
	{
		if (!Z_Registration_Info_UEnum_EXYZDecalType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXYZDecalType.InnerSingleton, Z_Construct_UEnum_XYZ_EXYZDecalType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EXYZDecalType.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZDecalType_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZDecalType_h_Statics::EnumInfo[] = {
		{ EXYZDecalType_StaticEnum, TEXT("EXYZDecalType"), &Z_Registration_Info_UEnum_EXYZDecalType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4026556723U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZDecalType_h_2639071235(TEXT("/Script/XYZ"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZDecalType_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZDecalType_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
