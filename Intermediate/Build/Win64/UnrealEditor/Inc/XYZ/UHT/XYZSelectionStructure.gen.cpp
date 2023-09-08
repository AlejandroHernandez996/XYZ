// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZSelectionStructure.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZSelectionStructure() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_AXYZActor_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZSelectionStructure();
	XYZ_API UClass* Z_Construct_UClass_UXYZSelectionStructure_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UXYZSelectionStructure::execContains)
	{
		P_GET_OBJECT(AXYZActor,Z_Param_Actor);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->Contains(Z_Param_Actor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZSelectionStructure::execToActorIdArray)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=P_THIS->ToActorIdArray();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UXYZSelectionStructure::execToArray)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<AXYZActor*>*)Z_Param__Result=P_THIS->ToArray();
		P_NATIVE_END;
	}
	void UXYZSelectionStructure::StaticRegisterNativesUXYZSelectionStructure()
	{
		UClass* Class = UXYZSelectionStructure::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Contains", &UXYZSelectionStructure::execContains },
			{ "ToActorIdArray", &UXYZSelectionStructure::execToActorIdArray },
			{ "ToArray", &UXYZSelectionStructure::execToArray },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics
	{
		struct XYZSelectionStructure_eventContains_Parms
		{
			AXYZActor* Actor;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZSelectionStructure_eventContains_Parms, Actor), Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((XYZSelectionStructure_eventContains_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(XYZSelectionStructure_eventContains_Parms), &Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::NewProp_Actor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZSelectionStructure.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZSelectionStructure, nullptr, "Contains", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::XYZSelectionStructure_eventContains_Parms), Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZSelectionStructure_Contains()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZSelectionStructure_Contains_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics
	{
		struct XYZSelectionStructure_eventToActorIdArray_Parms
		{
			TArray<int32> ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZSelectionStructure_eventToActorIdArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZSelectionStructure.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZSelectionStructure, nullptr, "ToActorIdArray", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::XYZSelectionStructure_eventToActorIdArray_Parms), Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics
	{
		struct XYZSelectionStructure_eventToArray_Parms
		{
			TArray<AXYZActor*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_AXYZActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZSelectionStructure_eventToArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZSelectionStructure.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZSelectionStructure, nullptr, "ToArray", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::XYZSelectionStructure_eventToArray_Parms), Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZSelectionStructure_ToArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZSelectionStructure_ToArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZSelectionStructure);
	UClass* Z_Construct_UClass_UXYZSelectionStructure_NoRegister()
	{
		return UXYZSelectionStructure::StaticClass();
	}
	struct Z_Construct_UClass_UXYZSelectionStructure_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZSelectionStructure_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UXYZSelectionStructure_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UXYZSelectionStructure_Contains, "Contains" }, // 2476977032
		{ &Z_Construct_UFunction_UXYZSelectionStructure_ToActorIdArray, "ToActorIdArray" }, // 359715135
		{ &Z_Construct_UFunction_UXYZSelectionStructure_ToArray, "ToArray" }, // 1560480229
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZSelectionStructure_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZSelectionStructure.h" },
		{ "ModuleRelativePath", "XYZSelectionStructure.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZSelectionStructure_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZSelectionStructure>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZSelectionStructure_Statics::ClassParams = {
		&UXYZSelectionStructure::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UXYZSelectionStructure_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZSelectionStructure_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZSelectionStructure()
	{
		if (!Z_Registration_Info_UClass_UXYZSelectionStructure.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZSelectionStructure.OuterSingleton, Z_Construct_UClass_UXYZSelectionStructure_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZSelectionStructure.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZSelectionStructure>()
	{
		return UXYZSelectionStructure::StaticClass();
	}
	UXYZSelectionStructure::UXYZSelectionStructure(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZSelectionStructure);
	UXYZSelectionStructure::~UXYZSelectionStructure() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZSelectionStructure, UXYZSelectionStructure::StaticClass, TEXT("UXYZSelectionStructure"), &Z_Registration_Info_UClass_UXYZSelectionStructure, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZSelectionStructure), 1040131356U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_965927696(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZSelectionStructure_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
