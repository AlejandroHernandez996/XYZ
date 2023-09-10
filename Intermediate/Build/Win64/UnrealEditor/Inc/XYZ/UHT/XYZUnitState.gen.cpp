// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZUnitState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZUnitState() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZUnitState();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXYZUnitState;
	static UEnum* EXYZUnitState_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EXYZUnitState.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EXYZUnitState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_XYZ_EXYZUnitState, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("EXYZUnitState"));
		}
		return Z_Registration_Info_UEnum_EXYZUnitState.OuterSingleton;
	}
	template<> XYZ_API UEnum* StaticEnum<EXYZUnitState>()
	{
		return EXYZUnitState_StaticEnum();
	}
	struct Z_Construct_UEnum_XYZ_EXYZUnitState_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::Enumerators[] = {
		{ "EXYZUnitState::IDLE", (int64)EXYZUnitState::IDLE },
		{ "EXYZUnitState::ATTACK", (int64)EXYZUnitState::ATTACK },
		{ "EXYZUnitState::HOLD", (int64)EXYZUnitState::HOLD },
		{ "EXYZUnitState::MOVE", (int64)EXYZUnitState::MOVE },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::Enum_MetaDataParams[] = {
		{ "ATTACK.Name", "EXYZUnitState::ATTACK" },
		{ "BlueprintType", "true" },
		{ "HOLD.Name", "EXYZUnitState::HOLD" },
		{ "IDLE.Name", "EXYZUnitState::IDLE" },
		{ "ModuleRelativePath", "XYZUnitState.h" },
		{ "MOVE.Name", "EXYZUnitState::MOVE" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		"EXYZUnitState",
		"EXYZUnitState",
		Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_XYZ_EXYZUnitState()
	{
		if (!Z_Registration_Info_UEnum_EXYZUnitState.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXYZUnitState.InnerSingleton, Z_Construct_UEnum_XYZ_EXYZUnitState_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EXYZUnitState.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnitState_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnitState_h_Statics::EnumInfo[] = {
		{ EXYZUnitState_StaticEnum, TEXT("EXYZUnitState"), &Z_Registration_Info_UEnum_EXYZUnitState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1534637437U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnitState_h_4109234682(TEXT("/Script/XYZ"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnitState_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUnitState_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
