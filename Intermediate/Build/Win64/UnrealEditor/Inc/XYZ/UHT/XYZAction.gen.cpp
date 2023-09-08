// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZAction() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction_NoRegister();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZActionState();
// End Cross Module References
	DEFINE_FUNCTION(UXYZAction::execIsFlaggedForDeuque)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsFlaggedForDeuque();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZAction::execCancelAction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CancelAction();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZAction::execCompleteAction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CompleteAction();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZAction::execStartAction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartAction();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZAction::execTryAction)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->TryAction(Z_Param_DeltaTime);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZAction::execProcessAction)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ProcessAction(Z_Param_DeltaTime);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZAction::execInitialize)
	{
		P_GET_OBJECT(AXYZActor,Z_Param__Actor);
		P_GET_OBJECT(AXYZActor,Z_Param__TargetActor);
		P_GET_STRUCT(FVector,Z_Param__TargetLocation);
		P_GET_UBOOL(Z_Param__bQueueInput);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Initialize(Z_Param__Actor,Z_Param__TargetActor,Z_Param__TargetLocation,Z_Param__bQueueInput);
		P_NATIVE_END;
	}
	void UXYZAction::StaticRegisterNativesUXYZAction()
	{
		UClass* Class = UXYZAction::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CancelAction", &UXYZAction::execCancelAction },
			{ "CompleteAction", &UXYZAction::execCompleteAction },
			{ "Initialize", &UXYZAction::execInitialize },
			{ "IsFlaggedForDeuque", &UXYZAction::execIsFlaggedForDeuque },
			{ "ProcessAction", &UXYZAction::execProcessAction },
			{ "StartAction", &UXYZAction::execStartAction },
			{ "TryAction", &UXYZAction::execTryAction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UXYZAction_CancelAction_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_CancelAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_CancelAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "CancelAction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_CancelAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_CancelAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_CancelAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_CancelAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZAction_CompleteAction_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_CompleteAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_CompleteAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "CompleteAction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_CompleteAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_CompleteAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_CompleteAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_CompleteAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZAction_Initialize_Statics
	{
		struct XYZAction_eventInitialize_Parms
		{
			AXYZActor* _Actor;
			AXYZActor* _TargetActor;
			FVector _TargetLocation;
			bool _bQueueInput;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp__Actor;
		static const UECodeGen_Private::FObjectPropertyParams NewProp__TargetActor;
		static const UECodeGen_Private::FStructPropertyParams NewProp__TargetLocation;
		static void NewProp__bQueueInput_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp__bQueueInput;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__Actor = { "_Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZAction_eventInitialize_Parms, _Actor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__TargetActor = { "_TargetActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZAction_eventInitialize_Parms, _TargetActor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__TargetLocation = { "_TargetLocation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZAction_eventInitialize_Parms, _TargetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__bQueueInput_SetBit(void* Obj)
	{
		((XYZAction_eventInitialize_Parms*)Obj)->_bQueueInput = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__bQueueInput = { "_bQueueInput", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(XYZAction_eventInitialize_Parms), &Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__bQueueInput_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZAction_Initialize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__Actor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__TargetActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__TargetLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_Initialize_Statics::NewProp__bQueueInput,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_Initialize_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_Initialize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "Initialize", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZAction_Initialize_Statics::XYZAction_eventInitialize_Parms), Z_Construct_UFunction_UXYZAction_Initialize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_Initialize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_Initialize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_Initialize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_Initialize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_Initialize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics
	{
		struct XYZAction_eventIsFlaggedForDeuque_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((XYZAction_eventIsFlaggedForDeuque_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(XYZAction_eventIsFlaggedForDeuque_Parms), &Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "IsFlaggedForDeuque", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::XYZAction_eventIsFlaggedForDeuque_Parms), Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZAction_ProcessAction_Statics
	{
		struct XYZAction_eventProcessAction_Parms
		{
			float DeltaTime;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZAction_eventProcessAction_Parms, DeltaTime), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::NewProp_DeltaTime,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "ProcessAction", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::XYZAction_eventProcessAction_Parms), Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_ProcessAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_ProcessAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZAction_StartAction_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_StartAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_StartAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "StartAction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_StartAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_StartAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_StartAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_StartAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZAction_TryAction_Statics
	{
		struct XYZAction_eventTryAction_Parms
		{
			float DeltaTime;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UXYZAction_TryAction_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZAction_eventTryAction_Parms, DeltaTime), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZAction_TryAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZAction_TryAction_Statics::NewProp_DeltaTime,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZAction_TryAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZAction_TryAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZAction, nullptr, "TryAction", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZAction_TryAction_Statics::XYZAction_eventTryAction_Parms), Z_Construct_UFunction_UXYZAction_TryAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_TryAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZAction_TryAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZAction_TryAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZAction_TryAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZAction_TryAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZAction);
	UClass* Z_Construct_UClass_UXYZAction_NoRegister()
	{
		return UXYZAction::StaticClass();
	}
	struct Z_Construct_UClass_UXYZAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetActor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_TargetLocation;
		static const UECodeGen_Private::FBytePropertyParams NewProp_ActionState_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActionState_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_ActionState;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Actor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bQueueInput_MetaData[];
#endif
		static void NewProp_bQueueInput_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bQueueInput;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UXYZAction_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UXYZAction_CancelAction, "CancelAction" }, // 4088306122
		{ &Z_Construct_UFunction_UXYZAction_CompleteAction, "CompleteAction" }, // 2484915420
		{ &Z_Construct_UFunction_UXYZAction_Initialize, "Initialize" }, // 599655581
		{ &Z_Construct_UFunction_UXYZAction_IsFlaggedForDeuque, "IsFlaggedForDeuque" }, // 1913108609
		{ &Z_Construct_UFunction_UXYZAction_ProcessAction, "ProcessAction" }, // 2564826730
		{ &Z_Construct_UFunction_UXYZAction_StartAction, "StartAction" }, // 1284247382
		{ &Z_Construct_UFunction_UXYZAction_TryAction, "TryAction" }, // 1175988595
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "XYZAction.h" },
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetActor_MetaData[] = {
		{ "Category", "Input" },
		{ "Comment", "// Target actor\n" },
		{ "ModuleRelativePath", "XYZAction.h" },
		{ "ToolTip", "Target actor" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetActor = { "TargetActor", nullptr, (EPropertyFlags)0x0020080000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAction, TargetActor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetActor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetLocation_MetaData[] = {
		{ "Category", "Action" },
		{ "Comment", "// Target location\n" },
		{ "ModuleRelativePath", "XYZAction.h" },
		{ "ToolTip", "Target location" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetLocation = { "TargetLocation", nullptr, (EPropertyFlags)0x0020080000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAction, TargetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetLocation_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState = { "ActionState", nullptr, (EPropertyFlags)0x0020080000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAction, ActionState), Z_Construct_UEnum_XYZ_EXYZActionState, METADATA_PARAMS(Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState_MetaData)) }; // 1876740357
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAction_Statics::NewProp_Actor_MetaData[] = {
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UXYZAction_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZAction, Actor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UXYZAction_Statics::NewProp_Actor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::NewProp_Actor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "XYZAction.h" },
	};
#endif
	void Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput_SetBit(void* Obj)
	{
		((UXYZAction*)Obj)->bQueueInput = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput = { "bQueueInput", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UXYZAction), &Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput_SetBit, METADATA_PARAMS(Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UXYZAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAction_Statics::NewProp_TargetLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAction_Statics::NewProp_ActionState,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAction_Statics::NewProp_Actor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZAction_Statics::NewProp_bQueueInput,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZAction_Statics::ClassParams = {
		&UXYZAction::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UXYZAction_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZAction()
	{
		if (!Z_Registration_Info_UClass_UXYZAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZAction.OuterSingleton, Z_Construct_UClass_UXYZAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZAction.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZAction>()
	{
		return UXYZAction::StaticClass();
	}
	UXYZAction::UXYZAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZAction);
	UXYZAction::~UXYZAction() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZAction, UXYZAction::StaticClass, TEXT("UXYZAction"), &Z_Registration_Info_UClass_UXYZAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZAction), 3522868732U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_619002970(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
