// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZResourceType.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZResourceType() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZResourceType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXYZResourceType;
	static UEnum* EXYZResourceType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EXYZResourceType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EXYZResourceType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_XYZ_EXYZResourceType, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("EXYZResourceType"));
		}
		return Z_Registration_Info_UEnum_EXYZResourceType.OuterSingleton;
	}
	template<> XYZ_API UEnum* StaticEnum<EXYZResourceType>()
	{
		return EXYZResourceType_StaticEnum();
	}
	struct Z_Construct_UEnum_XYZ_EXYZResourceType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::Enumerators[] = {
		{ "EXYZResourceType::MINERAL", (int64)EXYZResourceType::MINERAL },
		{ "EXYZResourceType::GAS", (int64)EXYZResourceType::GAS },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "GAS.Name", "EXYZResourceType::GAS" },
		{ "MINERAL.Name", "EXYZResourceType::MINERAL" },
		{ "ModuleRelativePath", "XYZResourceType.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		"EXYZResourceType",
		"EXYZResourceType",
		Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_XYZ_EXYZResourceType()
	{
		if (!Z_Registration_Info_UEnum_EXYZResourceType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXYZResourceType.InnerSingleton, Z_Construct_UEnum_XYZ_EXYZResourceType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EXYZResourceType.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZResourceType_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZResourceType_h_Statics::EnumInfo[] = {
		{ EXYZResourceType_StaticEnum, TEXT("EXYZResourceType"), &Z_Registration_Info_UEnum_EXYZResourceType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2392081031U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZResourceType_h_4243677896(TEXT("/Script/XYZ"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZResourceType_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZResourceType_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
