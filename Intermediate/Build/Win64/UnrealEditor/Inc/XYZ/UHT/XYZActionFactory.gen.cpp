// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZActionFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZActionFactory() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZActionFactory();
	XYZ_API UClass* Z_Construct_UClass_UXYZActionFactory_NoRegister();
	XYZ_API UEnum* Z_Construct_UEnum_XYZ_EXYZInputType();
// End Cross Module References
	DEFINE_FUNCTION(UXYZActionFactory::execMakeAction)
	{
		P_GET_OBJECT(AXYZActor,Z_Param__Actor);
		P_GET_OBJECT(AXYZActor,Z_Param__TargetActor);
		P_GET_STRUCT(FVector,Z_Param__TargetLocation);
		P_GET_UBOOL(Z_Param__bQueueInput);
		P_GET_ENUM(EXYZInputType,Z_Param_InputType);
		P_GET_PROPERTY(FIntProperty,Z_Param_ActionCount);
		P_GET_OBJECT(UClass,Z_Param_ActionClass);
		P_GET_PROPERTY(FNameProperty,Z_Param_ActionName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UXYZAction**)Z_Param__Result=UXYZActionFactory::MakeAction(Z_Param__Actor,Z_Param__TargetActor,Z_Param__TargetLocation,Z_Param__bQueueInput,EXYZInputType(Z_Param_InputType),Z_Param_ActionCount,Z_Param_ActionClass,Z_Param_ActionName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZActionFactory::execCreateAction)
	{
		P_GET_OBJECT(AXYZActor,Z_Param__Actor);
		P_GET_OBJECT(AXYZActor,Z_Param__TargetActor);
		P_GET_STRUCT(FVector,Z_Param__TargetLocation);
		P_GET_UBOOL(Z_Param__bQueueInput);
		P_GET_ENUM(EXYZInputType,Z_Param_InputType);
		P_GET_PROPERTY(FIntProperty,Z_Param_ActionCount);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UXYZAction**)Z_Param__Result=UXYZActionFactory::CreateAction(Z_Param__Actor,Z_Param__TargetActor,Z_Param__TargetLocation,Z_Param__bQueueInput,EXYZInputType(Z_Param_InputType),Z_Param_ActionCount);
		P_NATIVE_END;
	}
	void UXYZActionFactory::StaticRegisterNativesUXYZActionFactory()
	{
		UClass* Class = UXYZActionFactory::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateAction", &UXYZActionFactory::execCreateAction },
			{ "MakeAction", &UXYZActionFactory::execMakeAction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics
	{
		struct XYZActionFactory_eventCreateAction_Parms
		{
			AXYZActor* _Actor;
			AXYZActor* _TargetActor;
			FVector _TargetLocation;
			bool _bQueueInput;
			EXYZInputType InputType;
			int32 ActionCount;
			UXYZAction* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp__Actor;
		static const UECodeGen_Private::FObjectPropertyParams NewProp__TargetActor;
		static const UECodeGen_Private::FStructPropertyParams NewProp__TargetLocation;
		static void NewProp__bQueueInput_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp__bQueueInput;
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputType_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputType;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ActionCount;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__Actor = { "_Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventCreateAction_Parms, _Actor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__TargetActor = { "_TargetActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventCreateAction_Parms, _TargetActor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__TargetLocation = { "_TargetLocation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventCreateAction_Parms, _TargetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__bQueueInput_SetBit(void* Obj)
	{
		((XYZActionFactory_eventCreateAction_Parms*)Obj)->_bQueueInput = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__bQueueInput = { "_bQueueInput", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(XYZActionFactory_eventCreateAction_Parms), &Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__bQueueInput_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_InputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_InputType = { "InputType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventCreateAction_Parms, InputType), Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(nullptr, 0) }; // 1490979030
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_ActionCount = { "ActionCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventCreateAction_Parms, ActionCount), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventCreateAction_Parms, ReturnValue), Z_Construct_UClass_UXYZAction_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__Actor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__TargetActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__TargetLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp__bQueueInput,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_InputType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_InputType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_ActionCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::Function_MetaDataParams[] = {
		{ "Category", "Action" },
		{ "ModuleRelativePath", "XYZActionFactory.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZActionFactory, nullptr, "CreateAction", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::XYZActionFactory_eventCreateAction_Parms), Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZActionFactory_CreateAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZActionFactory_CreateAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics
	{
		struct XYZActionFactory_eventMakeAction_Parms
		{
			AXYZActor* _Actor;
			AXYZActor* _TargetActor;
			FVector _TargetLocation;
			bool _bQueueInput;
			EXYZInputType InputType;
			int32 ActionCount;
			UClass* ActionClass;
			FName ActionName;
			UXYZAction* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp__Actor;
		static const UECodeGen_Private::FObjectPropertyParams NewProp__TargetActor;
		static const UECodeGen_Private::FStructPropertyParams NewProp__TargetLocation;
		static void NewProp__bQueueInput_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp__bQueueInput;
		static const UECodeGen_Private::FBytePropertyParams NewProp_InputType_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_InputType;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ActionCount;
		static const UECodeGen_Private::FClassPropertyParams NewProp_ActionClass;
		static const UECodeGen_Private::FNamePropertyParams NewProp_ActionName;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__Actor = { "_Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, _Actor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__TargetActor = { "_TargetActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, _TargetActor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__TargetLocation = { "_TargetLocation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, _TargetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__bQueueInput_SetBit(void* Obj)
	{
		((XYZActionFactory_eventMakeAction_Parms*)Obj)->_bQueueInput = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__bQueueInput = { "_bQueueInput", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(XYZActionFactory_eventMakeAction_Parms), &Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__bQueueInput_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_InputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_InputType = { "InputType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, InputType), Z_Construct_UEnum_XYZ_EXYZInputType, METADATA_PARAMS(nullptr, 0) }; // 1490979030
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ActionCount = { "ActionCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, ActionCount), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ActionClass = { "ActionClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, ActionClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ActionName = { "ActionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, ActionName), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZActionFactory_eventMakeAction_Parms, ReturnValue), Z_Construct_UClass_UXYZAction_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__Actor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__TargetActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__TargetLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp__bQueueInput,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_InputType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_InputType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ActionCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ActionClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ActionName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::Function_MetaDataParams[] = {
		{ "Category", "Action" },
		{ "ModuleRelativePath", "XYZActionFactory.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZActionFactory, nullptr, "MakeAction", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::XYZActionFactory_eventMakeAction_Parms), Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZActionFactory_MakeAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZActionFactory_MakeAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZActionFactory);
	UClass* Z_Construct_UClass_UXYZActionFactory_NoRegister()
	{
		return UXYZActionFactory::StaticClass();
	}
	struct Z_Construct_UClass_UXYZActionFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZActionFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UXYZActionFactory_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UXYZActionFactory_CreateAction, "CreateAction" }, // 1143119473
		{ &Z_Construct_UFunction_UXYZActionFactory_MakeAction, "MakeAction" }, // 1645876900
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZActionFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZActionFactory.h" },
		{ "ModuleRelativePath", "XYZActionFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZActionFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZActionFactory>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZActionFactory_Statics::ClassParams = {
		&UXYZActionFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZActionFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZActionFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZActionFactory()
	{
		if (!Z_Registration_Info_UClass_UXYZActionFactory.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZActionFactory.OuterSingleton, Z_Construct_UClass_UXYZActionFactory_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZActionFactory.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZActionFactory>()
	{
		return UXYZActionFactory::StaticClass();
	}
	UXYZActionFactory::UXYZActionFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZActionFactory);
	UXYZActionFactory::~UXYZActionFactory() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionFactory_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionFactory_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZActionFactory, UXYZActionFactory::StaticClass, TEXT("UXYZActionFactory"), &Z_Registration_Info_UClass_UXYZActionFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZActionFactory), 1681562602U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionFactory_h_3952957361(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActionFactory_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
