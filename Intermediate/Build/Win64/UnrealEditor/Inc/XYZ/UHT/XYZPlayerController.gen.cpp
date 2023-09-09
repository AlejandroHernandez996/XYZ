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
	XYZ_API UClass* Z_Construct_UClass_UXYZSelectionStructure_NoRegister();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZInputType();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature();
	XYZ_API UScriptStruct* Z_Construct_UScriptStruct_FXYZInputMessage();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics
	{
		struct _Script_XYZ_eventSelectionBoxEvent_Parms
		{
			float x;
			float y;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_x;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_y;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::NewProp_x = { "x", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_XYZ_eventSelectionBoxEvent_Parms, x), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::NewProp_y = { "y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_XYZ_eventSelectionBoxEvent_Parms, y), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::NewProp_x,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::NewProp_y,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_XYZ, nullptr, "SelectionBoxEvent__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::_Script_XYZ_eventSelectionBoxEvent_Parms), Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FSelectionBoxEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionBoxEvent, float x, float y)
{
	struct _Script_XYZ_eventSelectionBoxEvent_Parms
	{
		float x;
		float y;
	};
	_Script_XYZ_eventSelectionBoxEvent_Parms Parms;
	Parms.x=x;
	Parms.y=y;
	SelectionBoxEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
	struct Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics
	{
		struct _Script_XYZ_eventSelectionBoxTriggeredEvent_Parms
		{
			float x;
			float y;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_x;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_y;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::NewProp_x = { "x", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_XYZ_eventSelectionBoxTriggeredEvent_Parms, x), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::NewProp_y = { "y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_XYZ_eventSelectionBoxTriggeredEvent_Parms, y), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::NewProp_x,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::NewProp_y,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_XYZ, nullptr, "SelectionBoxTriggeredEvent__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::_Script_XYZ_eventSelectionBoxTriggeredEvent_Parms), Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FSelectionBoxTriggeredEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionBoxTriggeredEvent, float x, float y)
{
	struct _Script_XYZ_eventSelectionBoxTriggeredEvent_Parms
	{
		float x;
		float y;
	};
	_Script_XYZ_eventSelectionBoxTriggeredEvent_Parms Parms;
	Parms.x=x;
	Parms.y=y;
	SelectionBoxTriggeredEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
	struct Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics
	{
		struct _Script_XYZ_eventSelectionBoxReleasedEvent_Parms
		{
			float x;
			float y;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_x;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_y;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::NewProp_x = { "x", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_XYZ_eventSelectionBoxReleasedEvent_Parms, x), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::NewProp_y = { "y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_XYZ_eventSelectionBoxReleasedEvent_Parms, y), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::NewProp_x,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::NewProp_y,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_XYZ, nullptr, "SelectionBoxReleasedEvent__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::_Script_XYZ_eventSelectionBoxReleasedEvent_Parms), Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FSelectionBoxReleasedEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionBoxReleasedEvent, float x, float y)
{
	struct _Script_XYZ_eventSelectionBoxReleasedEvent_Parms
	{
		float x;
		float y;
	};
	_Script_XYZ_eventSelectionBoxReleasedEvent_Parms Parms;
	Parms.x=x;
	Parms.y=y;
	SelectionBoxReleasedEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
	DEFINE_FUNCTION(AXYZPlayerController::execQueueInput)
	{
		P_GET_STRUCT(FXYZInputMessage,Z_Param_InputMessage);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->QueueInput_Implementation(Z_Param_InputMessage);
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
	DEFINE_FUNCTION(AXYZPlayerController::execOnControlGroupInputStarted)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ControlGroupIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnControlGroupInputStarted(Z_Param_ControlGroupIndex);
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
			{ "GetMousePositionOnViewport", &AXYZPlayerController::execGetMousePositionOnViewport },
			{ "OnControlGroupInputStarted", &AXYZPlayerController::execOnControlGroupInputStarted },
			{ "OnInputReleased", &AXYZPlayerController::execOnInputReleased },
			{ "OnInputStarted", &AXYZPlayerController::execOnInputStarted },
			{ "OnInputTriggered", &AXYZPlayerController::execOnInputTriggered },
			{ "QueueInput", &AXYZPlayerController::execQueueInput },
			{ "SelectActors", &AXYZPlayerController::execSelectActors },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
	struct Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics
	{
		struct XYZPlayerController_eventOnControlGroupInputStarted_Parms
		{
			int32 ControlGroupIndex;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ControlGroupIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::NewProp_ControlGroupIndex = { "ControlGroupIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventOnControlGroupInputStarted_Parms, ControlGroupIndex), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::NewProp_ControlGroupIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AXYZPlayerController, nullptr, "OnControlGroupInputStarted", nullptr, nullptr, sizeof(Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::XYZPlayerController_eventOnControlGroupInputStarted_Parms), Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted_Statics::FuncParams);
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage = { "InputMessage", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZPlayerController_eventQueueInput_Parms, InputMessage), Z_Construct_UScriptStruct_FXYZInputMessage, METADATA_PARAMS(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AXYZPlayerController_QueueInput_Statics::NewProp_InputMessage_MetaData)) }; // 4208671430
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputTriggeredCooldown_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_InputTriggeredCooldown;
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
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ControlGroupInputActions_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ControlGroupInputActions_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ControlGroupInputActions;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BoxSelectStart_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_BoxSelectStart;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BoxSelectEnd_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_BoxSelectEnd;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnSelectionBox_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSelectionBox;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnSelectionBoxTriggered_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSelectionBoxTriggered;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnSelectionBoxReleased_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSelectionBoxReleased;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SelectionStructure_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectionStructure;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_InputTriggeredTime_ValueProp;
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputTriggeredTime_Key_KeyProp_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputTriggeredTime_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputTriggeredTime_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_InputTriggeredTime;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXYZPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AXYZPlayerController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AXYZPlayerController_GetMousePositionOnViewport, "GetMousePositionOnViewport" }, // 4017315989
		{ &Z_Construct_UFunction_AXYZPlayerController_OnControlGroupInputStarted, "OnControlGroupInputStarted" }, // 3978032771
		{ &Z_Construct_UFunction_AXYZPlayerController_OnInputReleased, "OnInputReleased" }, // 2115070104
		{ &Z_Construct_UFunction_AXYZPlayerController_OnInputStarted, "OnInputStarted" }, // 3989164957
		{ &Z_Construct_UFunction_AXYZPlayerController_OnInputTriggered, "OnInputTriggered" }, // 230609579
		{ &Z_Construct_UFunction_AXYZPlayerController_QueueInput, "QueueInput" }, // 1884853875
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredCooldown_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredCooldown = { "InputTriggeredCooldown", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, InputTriggeredCooldown), METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredCooldown_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredCooldown_MetaData)) };
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions_Inner = { "ControlGroupInputActions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions = { "ControlGroupInputActions", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, ControlGroupInputActions), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions_MetaData)) };
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
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBox_MetaData[] = {
		{ "Category", "Events" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBox = { "OnSelectionBox", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, OnSelectionBox), Z_Construct_UDelegateFunction_XYZ_SelectionBoxEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBox_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBox_MetaData)) }; // 2013443236
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxTriggered_MetaData[] = {
		{ "Category", "Events" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxTriggered = { "OnSelectionBoxTriggered", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, OnSelectionBoxTriggered), Z_Construct_UDelegateFunction_XYZ_SelectionBoxTriggeredEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxTriggered_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxTriggered_MetaData)) }; // 1933092671
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxReleased_MetaData[] = {
		{ "Category", "Events" },
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxReleased = { "OnSelectionBoxReleased", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, OnSelectionBoxReleased), Z_Construct_UDelegateFunction_XYZ_SelectionBoxReleasedEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxReleased_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxReleased_MetaData)) }; // 2329107380
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SelectionStructure_MetaData[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SelectionStructure = { "SelectionStructure", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, SelectionStructure), Z_Construct_UClass_UXYZSelectionStructure_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SelectionStructure_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SelectionStructure_MetaData)) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_ValueProp = { "InputTriggeredTime", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_Key_KeyProp = { "InputTriggeredTime_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(nullptr, 0) }; // 1699687832
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_MetaData[] = {
		{ "ModuleRelativePath", "XYZPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime = { "InputTriggeredTime", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AXYZPlayerController, InputTriggeredTime), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_MetaData)) }; // 1699687832
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AXYZPlayerController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ShortInputThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredCooldown,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_FXCursor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_DefaultMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_AttackMoveInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_StopInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_PrimaryModifierInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SecondaryModifierInputAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_ControlGroupInputActions,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectStart,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_BoxSelectEnd,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBox,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxTriggered,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_OnSelectionBoxReleased,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_SelectionStructure,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_Key_KeyProp_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AXYZPlayerController_Statics::NewProp_InputTriggeredTime,
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
		{ Z_Construct_UClass_AXYZPlayerController, AXYZPlayerController::StaticClass, TEXT("AXYZPlayerController"), &Z_Registration_Info_UClass_AXYZPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXYZPlayerController), 1530315418U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_581734120(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
