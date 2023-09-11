// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZBlobFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZBlobFactory() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZAction_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlob_NoRegister();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlobFactory();
	XYZ_API UClass* Z_Construct_UClass_UXYZBlobFactory_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UXYZBlobFactory::execCreateBlobFromAction)
	{
		P_GET_OBJECT(UXYZAction,Z_Param_Action);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UXYZBlob**)Z_Param__Result=UXYZBlobFactory::CreateBlobFromAction(Z_Param_Action);
		P_NATIVE_END;
	}
	void UXYZBlobFactory::StaticRegisterNativesUXYZBlobFactory()
	{
		UClass* Class = UXYZBlobFactory::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateBlobFromAction", &UXYZBlobFactory::execCreateBlobFromAction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics
	{
		struct XYZBlobFactory_eventCreateBlobFromAction_Parms
		{
			const UXYZAction* Action;
			UXYZBlob* ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Action_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Action;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_Action_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZBlobFactory_eventCreateBlobFromAction_Parms, Action), Z_Construct_UClass_UXYZAction_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_Action_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_Action_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(XYZBlobFactory_eventCreateBlobFromAction_Parms, ReturnValue), Z_Construct_UClass_UXYZBlob_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_Action,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZBlobFactory.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UXYZBlobFactory, nullptr, "CreateBlobFromAction", nullptr, nullptr, sizeof(Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::XYZBlobFactory_eventCreateBlobFromAction_Parms), Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZBlobFactory);
	UClass* Z_Construct_UClass_UXYZBlobFactory_NoRegister()
	{
		return UXYZBlobFactory::StaticClass();
	}
	struct Z_Construct_UClass_UXYZBlobFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZBlobFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UXYZBlobFactory_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UXYZBlobFactory_CreateBlobFromAction, "CreateBlobFromAction" }, // 3862164672
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZBlobFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "XYZBlobFactory.h" },
		{ "ModuleRelativePath", "XYZBlobFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZBlobFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZBlobFactory>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZBlobFactory_Statics::ClassParams = {
		&UXYZBlobFactory::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UXYZBlobFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZBlobFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZBlobFactory()
	{
		if (!Z_Registration_Info_UClass_UXYZBlobFactory.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZBlobFactory.OuterSingleton, Z_Construct_UClass_UXYZBlobFactory_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZBlobFactory.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZBlobFactory>()
	{
		return UXYZBlobFactory::StaticClass();
	}
	UXYZBlobFactory::UXYZBlobFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZBlobFactory);
	UXYZBlobFactory::~UXYZBlobFactory() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobFactory_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobFactory_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZBlobFactory, UXYZBlobFactory::StaticClass, TEXT("UXYZBlobFactory"), &Z_Registration_Info_UClass_UXYZBlobFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZBlobFactory), 2970741336U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobFactory_h_592945526(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZBlobFactory_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
