// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZFactionType.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZFactionType() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZFactionType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXYZFactionType;
	static UEnum* EXYZFactionType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EXYZFactionType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EXYZFactionType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_XYZ_EXYZFactionType, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("EXYZFactionType"));
		}
		return Z_Registration_Info_UEnum_EXYZFactionType.OuterSingleton;
	}
	template<> XYZ_API UEnum* StaticEnum<EXYZFactionType>()
	{
		return EXYZFactionType_StaticEnum();
	}
	struct Z_Construct_UEnum_XYZ_EXYZFactionType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::Enumerators[] = {
		{ "EXYZFactionType::X", (int64)EXYZFactionType::X },
		{ "EXYZFactionType::Y", (int64)EXYZFactionType::Y },
		{ "EXYZFactionType::Z", (int64)EXYZFactionType::Z },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "XYZFactionType.h" },
		{ "X.Name", "EXYZFactionType::X" },
		{ "Y.Name", "EXYZFactionType::Y" },
		{ "Z.Name", "EXYZFactionType::Z" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		"EXYZFactionType",
		"EXYZFactionType",
		Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_XYZ_EXYZFactionType()
	{
		if (!Z_Registration_Info_UEnum_EXYZFactionType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXYZFactionType.InnerSingleton, Z_Construct_UEnum_XYZ_EXYZFactionType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EXYZFactionType.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZFactionType_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZFactionType_h_Statics::EnumInfo[] = {
		{ EXYZFactionType_StaticEnum, TEXT("EXYZFactionType"), &Z_Registration_Info_UEnum_EXYZFactionType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3193192588U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZFactionType_h_786173201(TEXT("/Script/XYZ"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZFactionType_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZFactionType_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
