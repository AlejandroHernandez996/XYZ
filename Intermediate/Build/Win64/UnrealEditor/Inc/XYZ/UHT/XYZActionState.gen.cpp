// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZActionState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZActionState() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZActionState();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXYZActionState;
	static UEnum* EXYZActionState_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EXYZActionState.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EXYZActionState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_XYZ_EXYZActionState, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("EXYZActionState"));
		}
		return Z_Registration_Info_UEnum_EXYZActionState.OuterSingleton;
	}
	template<> XYZ_API UEnum* StaticEnum<EXYZActionState>()
	{
		return EXYZActionState_StaticEnum();
	}
	struct Z_Construct_UEnum_XYZ_EXYZActionState_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_XYZ_EXYZActionState_Statics::Enumerators[] = {
		{ "EXYZActionState::QUEUED", (int64)EXYZActionState::QUEUED },
		{ "EXYZActionState::IN_PROGRESS", (int64)EXYZActionState::IN_PROGRESS },
		{ "EXYZActionState::COMPLETE", (int64)EXYZActionState::COMPLETE },
		{ "EXYZActionState::CANCELLED", (int64)EXYZActionState::CANCELLED },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_XYZ_EXYZActionState_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CANCELLED.Name", "EXYZActionState::CANCELLED" },
		{ "COMPLETE.Name", "EXYZActionState::COMPLETE" },
		{ "IN_PROGRESS.Name", "EXYZActionState::IN_PROGRESS" },
		{ "ModuleRelativePath", "XYZActionState.h" },
		{ "QUEUED.Name", "EXYZActionState::QUEUED" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_XYZ_EXYZActionState_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		"EXYZActionState",
		"EXYZActionState",
		Z_Construct_UEnum_XYZ_EXYZActionState_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZActionState_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_XYZ_EXYZActionState_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_XYZ_EXYZActionState_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_XYZ_EXYZActionState()
	{
		if (!Z_Registration_Info_UEnum_EXYZActionState.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXYZActionState.InnerSingleton, Z_Construct_UEnum_XYZ_EXYZActionState_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EXYZActionState.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionState_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionState_h_Statics::EnumInfo[] = {
		{ EXYZActionState_StaticEnum, TEXT("EXYZActionState"), &Z_Registration_Info_UEnum_EXYZActionState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1876740357U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionState_h_1781611412(TEXT("/Script/XYZ"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionState_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionState_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
