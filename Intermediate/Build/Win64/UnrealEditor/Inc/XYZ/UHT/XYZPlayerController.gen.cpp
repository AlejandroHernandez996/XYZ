// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZPlayerController.h"
#include "XYZ/XYZInputMessage.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZPlayerController() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	NIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystem_NoRegister();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_AXYZPlayerController();
	XYZ_API UClass* Z_Construct_UClass_AXYZPlayerController_NoRegister();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZInputType();
	XYZ_API UScriptStruct* Z_Construct_UScriptStruct_FXYZInputMessage();
// End Cross Module References
	DEFINE_FUNCTION(AXYZPlayerController::execQueueInput)
	{
		P_GET_STRUCT(FXYZInputMessage,Z_Param_InputMessage);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->QueueInput_Implementation(Z_Param_InputMessage);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AXYZPlayerController::execAddActorToSelection)
	{
		P_GET_OBJECT(AXYZActor,Z_Param_Actor);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddActorToSelection(Z_Param_Actor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AXYZPlayerController::execSelectActors)
	{
		P_GET_TARRAY(AXYZActor*,Z_Param_Actors);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SelectActors(Z_Param_Actors);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AXYZPlayerController::execOnInputReleased)
	{
		P_GET_ENUM(EXYZInputType,Z_Param_InputType);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnInputReleased(EXYZInputType(Z_Param_InputType));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AXYZPlayerController::execOnInputTriggered)
	{
		P_GET_ENUM(EXYZInputType,Z_Param_InputType);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnInputTriggered(EXYZInputType(Z_Param_InputType));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AXYZPlayerController::execOnInputStarted)
	{
		P_GET_ENUM(EXYZInputType,Z_Param_InputType);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnInputStarted(EXYZInputType(Z_Param_InputType));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AXYZPlayerController::execGetMousePositionOnViewport)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector2D*)Z_Param__Result=P_THIS->GetMousePositionOnViewport();
		P_NATIVE_END;
	}
	struct XYZPlayerController_eventQueueInput_Parms
	{
		FXYZInputMessage InputMessage;
	};
	static FName NAME_AXYZPlayerController_QueueInput = FName(TEXT("QueueInput"));
	void AXYZPlayerController::QueueInput(FXYZInputMessage const& InputMessage)
	{
		XYZPlayerController_eventQueueInput_Parms Parms;
		Parms.InputMessage=InputMessage;
		ProcessEvent(FindFunctionChecked(NAME_AXYZPlayerController_QueueInput),&Parms);
	}
	void AXYZPlayerController::StaticRegisterNativesAXYZPlayerController()
	{
		UClass* Class = AXYZPlayerController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddActorToSelection", &AXYZPlayerController::execAddActorToSelection },
			{ "GetMousePositionOnViewport", &AXYZPlayerController::execGetMousePositionOnViewport },
			{ "OnInputReleased", &AXYZPlayerController::execOnInputReleased },
			{ "OnInputStarted", &AXYZPlayerController::execOnInputStarted },
			{ "OnInputTriggered", &AXYZPlayerController::execOnInputTriggered },
			{ "QueueInput", &AXYZPlayerController::execQueueInput },
			{ "SelectActors", &AXYZPlayerController::execSelectActors },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics
	{
		struct XYZPlayerController_eventAddActorToSelection_Parms
		{
			AXYZActor* Actor;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventAddActorToSelection_Parms, Actor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::NewProp_Actor,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "AddActorToSelection", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::XYZPlayerController_eventAddActorToSelection_Parms), Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics
	{
		struct XYZPlayerController_eventGetMousePositionOnViewport_Parms
		{
			FVector2D ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventGetMousePositionOnViewport_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "GetMousePositionOnViewport", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::XYZPlayerController_eventGetMousePositionOnViewport_Parms), Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics
	{
		struct XYZPlayerController_eventOnInputReleased_Parms
		{
			EXYZInputType InputType;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputType_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputType;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::NewProp_InputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::NewProp_InputType = { "InputType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventOnInputReleased_Parms, InputType), Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(nullptr, 0) }; // 1699687832
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::NewProp_InputType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::NewProp_InputType,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "OnInputReleased", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::XYZPlayerController_eventOnInputReleased_Parms), Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_OnInputReleased()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_OnInputReleased_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics
	{
		struct XYZPlayerController_eventOnInputStarted_Parms
		{
			EXYZInputType InputType;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputType_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputType;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::NewProp_InputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::NewProp_InputType = { "InputType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventOnInputStarted_Parms, InputType), Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(nullptr, 0) }; // 1699687832
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::NewProp_InputType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::NewProp_InputType,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Input handlers for SetDestination action. */" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "Input handlers for SetDestination action." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "OnInputStarted", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::XYZPlayerController_eventOnInputStarted_Parms), Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_OnInputStarted()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_OnInputStarted_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics
	{
		struct XYZPlayerController_eventOnInputTriggered_Parms
		{
			EXYZInputType InputType;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputType_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputType;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::NewProp_InputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::NewProp_InputType = { "InputType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventOnInputTriggered_Parms, InputType), Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(nullptr, 0) }; // 1699687832
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::NewProp_InputType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::NewProp_InputType,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "OnInputTriggered", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::XYZPlayerController_eventOnInputTriggered_Parms), Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputMessage_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InputMessage;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage = { "InputMessage", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventQueueInput_Parms, InputMessage), Z_Construct_UScriptStruct_FXYZInputMessage, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage_MetaData)) }; // 28926835
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "QueueInput", nullptr, nullptr, sizeof(XYZPlayerController_eventQueueInput_Parms), Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00280CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_QueueInput()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics
	{
		struct XYZPlayerController_eventSelectActors_Parms
		{
			TArray<AXYZActor*> Actors;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Actors_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Actors;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::NewProp_Actors_Inner = { "Actors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::NewProp_Actors = { "Actors", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventSelectActors_Parms, Actors), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::NewProp_Actors_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::NewProp_Actors,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "SelectActors", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::XYZPlayerController_eventSelectActors_Parms), Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_SelectActors()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_SelectActors_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXYZPlayerController);
	UClass* Z_Construct_UClass_AXYZPlayerController_NoRegister()
	{
		return AXYZPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_AXYZPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ShortInputThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ShortInputThreshold;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FXCursor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FXCursor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryInputAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_PrimaryInputAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryInputAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SecondaryInputAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackMoveInputAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackMoveInputAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StopInputAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_StopInputAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryModifierInputAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_PrimaryModifierInputAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryModifierInputAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SecondaryModifierInputAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BoxSelectStart_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_BoxSelectStart;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BoxSelectEnd_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_BoxSelectEnd;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AXYZPlayerController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AXYZPlayerController_AddActorToSelection, "AddActorToSelection" }, // 3104993149
		{ &Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport, "GetMousePositionOnViewport" }, // 4017315989
		{ &Z_Construct_UFunction_AXYZPlayerController_OnInputReleased, "OnInputReleased" }, // 2115070104
		{ &Z_Construct_UFunction_AXYZPlayerController_OnInputStarted, "OnInputStarted" }, // 3989164957
		{ &Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered, "OnInputTriggered" }, // 230609579
		{ &Z_Construct_UFunction_AXYZPlayerController_QueueInput, "QueueInput" }, // 1088251476
		{ &Z_Construct_UFunction_AXYZPlayerController_SelectActors, "SelectActors" }, // 1853716492
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "XYZPlayerController.h" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ShortInputThreshold_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "/** Time Threshold to know if it was a short press */" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "Time Threshold to know if it was a short press" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ShortInputThreshold = { "ShortInputThreshold", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, ShortInputThreshold), METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ShortInputThreshold_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ShortInputThreshold_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_FXCursor_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "/** FX Class that we will spawn when clicking */" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "FX Class that we will spawn when clicking" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_FXCursor = { "FXCursor", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, FXCursor), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_FXCursor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_FXCursor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "Comment", "/** MappingContext */" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "MappingContext" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_DefaultMappingContext_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_DefaultMappingContext_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryInputAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "Comment", "/** SELECT BOX INPUT - SELECT SINGLE INPUT **/" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "SELECT BOX INPUT - SELECT SINGLE INPUT *" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryInputAction = { "PrimaryInputAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, PrimaryInputAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryInputAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryInputAction_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryInputAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "Comment", "/** MOVE - ATTACK**/" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "MOVE - ATTACK*" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryInputAction = { "SecondaryInputAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, SecondaryInputAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryInputAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryInputAction_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_AttackMoveInputAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_AttackMoveInputAction = { "AttackMoveInputAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, AttackMoveInputAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_AttackMoveInputAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_AttackMoveInputAction_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_StopInputAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_StopInputAction = { "StopInputAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, StopInputAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_StopInputAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_StopInputAction_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryModifierInputAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "Comment", "/** ADD TO SELECTION - QUEUE INPUT **/" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "ADD TO SELECTION - QUEUE INPUT *" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryModifierInputAction = { "PrimaryModifierInputAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, PrimaryModifierInputAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryModifierInputAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryModifierInputAction_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryModifierInputAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "Comment", "/** SELECT ALL OF TYPE **/" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
		{ "ToolTip", "SELECT ALL OF TYPE *" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryModifierInputAction = { "SecondaryModifierInputAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, SecondaryModifierInputAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryModifierInputAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryModifierInputAction_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectStart_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectStart = { "BoxSelectStart", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, BoxSelectStart), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectStart_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectStart_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectEnd_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectEnd = { "BoxSelectEnd", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, BoxSelectEnd), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectEnd_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectEnd_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AXYZPlayerController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ShortInputThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_FXCursor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_DefaultMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_AttackMoveInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_StopInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryModifierInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryModifierInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectStart,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectEnd,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXYZPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXYZPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXYZPlayerController_Statics::ClassParams = {
		&AXYZPlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AXYZPlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::PropPointers),
		0,
		0x008002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXYZPlayerController()
	{
		if (!Z_Registration_Info_UClass_AXYZPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXYZPlayerController.OuterSingleton, Z_Construct_UClass_AXYZPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXYZPlayerController.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<AXYZPlayerController>()
	{
		return AXYZPlayerController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXYZPlayerController);
	AXYZPlayerController::~AXYZPlayerController() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXYZPlayerController, AXYZPlayerController::StaticClass, TEXT("AXYZPlayerController"), &Z_Registration_Info_UClass_AXYZPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZPlayerController), 1025576579U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_1023235355(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
