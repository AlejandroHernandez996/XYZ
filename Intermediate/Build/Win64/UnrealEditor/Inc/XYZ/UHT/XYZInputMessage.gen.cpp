// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZInputMessage.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZInputMessage() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZInputType();
	XYZ_API UScriptStruct* Z_Construct_UScriptStruct_FXYZInputMessage();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_XYZInputMessage;
class UScriptStruct* FXYZInputMessage::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_XYZInputMessage.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_XYZInputMessage.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FXYZInputMessage, (UObject*)Z_Construct_UPackage__Script_XYZ(), TEXT("XYZInputMessage"));
	}
	return Z_Registration_Info_UScriptStruct_XYZInputMessage.OuterSingleton;
}
template<> XYZ_API UScriptStruct* StaticStruct<FXYZInputMessage>()
{
	return FXYZInputMessage::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FXYZInputMessage_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PlayerId;
		static const UECodeGen_Private::FIntPropertyParams NewProp_SelectedActors_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SelectedActors_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_SelectedActors;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_XYZTargetActor_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_XYZTargetActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_TargetLocation;
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bQueueInput_MetaData[];
#endif
		static void NewProp_bQueueInput_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bQueueInput;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tick_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Tick;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FXYZInputMessage>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_PlayerId_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "// Player ID\n" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
		{ "ToolTip", "Player ID" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_PlayerId = { "PlayerId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FXYZInputMessage, PlayerId), METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_PlayerId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_PlayerId_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors_Inner = { "SelectedActors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors_MetaData[] = {
		{ "Comment", "// Array of selected units\n" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
		{ "ToolTip", "Array of selected units" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors = { "SelectedActors", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FXYZInputMessage, SelectedActors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_XYZTargetActor_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "// Target actor\n" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
		{ "ToolTip", "Target actor" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_XYZTargetActor = { "XYZTargetActor", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FXYZInputMessage, XYZTargetActor), METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_XYZTargetActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_XYZTargetActor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_TargetLocation_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "// Target location\n" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
		{ "ToolTip", "Target location" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_TargetLocation = { "TargetLocation", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FXYZInputMessage, TargetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_TargetLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_TargetLocation_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "// Type of input\n" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
		{ "ToolTip", "Type of input" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType = { "InputType", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FXYZInputMessage, InputType), Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType_MetaData)) }; // 1699687832
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZInputMessage.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput_SetBit(void* Obj)
	{
		((FXYZInputMessage*)Obj)->bQueueInput = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput = { "bQueueInput", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(FXYZInputMessage), &Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_Tick_MetaData[] = {
		{ "ModuleRelativePath", "XYZInputMessage.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_Tick = { "Tick", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FXYZInputMessage, Tick), METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_Tick_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_Tick_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FXYZInputMessage_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_PlayerId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_SelectedActors,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_XYZTargetActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_TargetLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_InputType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_bQueueInput,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewProp_Tick,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FXYZInputMessage_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
		nullptr,
		&NewStructOps,
		"XYZInputMessage",
		sizeof(FXYZInputMessage),
		alignof(FXYZInputMessage),
		Z_Construct_UScriptStruct_FXYZInputMessage_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FXYZInputMessage_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FXYZInputMessage()
	{
		if (!Z_Registration_Info_UScriptStruct_XYZInputMessage.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_XYZInputMessage.InnerSingleton, Z_Construct_UScriptStruct_FXYZInputMessage_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_XYZInputMessage.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputMessage_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputMessage_h_Statics::ScriptStructInfo[] = {
		{ FXYZInputMessage::StaticStruct, Z_Construct_UScriptStruct_FXYZInputMessage_Statics::NewStructOps, TEXT("XYZInputMessage"), &Z_Registration_Info_UScriptStruct_XYZInputMessage, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FXYZInputMessage), 4208671430U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputMessage_h_1589205938(TEXT("/Script/XYZ"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputMessage_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZInputMessage_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
