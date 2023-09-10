// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZ/XYZUserWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXYZUserWidget() {}
// Cross Module References
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_XYZ();
	XYZ_API UClass* Z_Construct_UClass_UXYZUserWidget();
	XYZ_API UClass* Z_Construct_UClass_UXYZUserWidget_NoRegister();
	XYZ_API UFunction* Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "XYZUserWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_XYZ, nullptr, "OnMouseHoveredEvent__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FOnMouseHoveredEvent_DelegateWrapper(const FMulticastScriptDelegate& OnMouseHoveredEvent)
{
	OnMouseHoveredEvent.ProcessMulticastDelegate<UObject>(NULL);
}
	void UXYZUserWidget::StaticRegisterNativesUXYZUserWidget()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXYZUserWidget);
	UClass* Z_Construct_UClass_UXYZUserWidget_NoRegister()
	{
		return UXYZUserWidget::StaticClass();
	}
	struct Z_Construct_UClass_UXYZUserWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsMouseHovered_MetaData[];
#endif
		static void NewProp_bIsMouseHovered_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsMouseHovered;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnMouseHovered_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnMouseHovered;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXYZUserWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZ,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZUserWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "XYZUserWidget.h" },
		{ "ModuleRelativePath", "XYZUserWidget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered_MetaData[] = {
		{ "Category", "Mouse" },
		{ "ModuleRelativePath", "XYZUserWidget.h" },
	};
#endif
	void Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered_SetBit(void* Obj)
	{
		((UXYZUserWidget*)Obj)->bIsMouseHovered = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered = { "bIsMouseHovered", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UXYZUserWidget), &Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered_SetBit, METADATA_PARAMS(Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_OnMouseHovered_MetaData[] = {
		{ "Category", "Mouse" },
		{ "ModuleRelativePath", "XYZUserWidget.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_OnMouseHovered = { "OnMouseHovered", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UXYZUserWidget, OnMouseHovered), Z_Construct_UDelegateFunction_XYZ_OnMouseHoveredEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_OnMouseHovered_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_OnMouseHovered_MetaData)) }; // 2846012954
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UXYZUserWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_bIsMouseHovered,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UXYZUserWidget_Statics::NewProp_OnMouseHovered,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXYZUserWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXYZUserWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXYZUserWidget_Statics::ClassParams = {
		&UXYZUserWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UXYZUserWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UXYZUserWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UXYZUserWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXYZUserWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXYZUserWidget()
	{
		if (!Z_Registration_Info_UClass_UXYZUserWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXYZUserWidget.OuterSingleton, Z_Construct_UClass_UXYZUserWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXYZUserWidget.OuterSingleton;
	}
	template<> XYZ_API UClass* StaticClass<UXYZUserWidget>()
	{
		return UXYZUserWidget::StaticClass();
	}
	UXYZUserWidget::UXYZUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXYZUserWidget);
	UXYZUserWidget::~UXYZUserWidget() {}
	struct Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUserWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUserWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXYZUserWidget, UXYZUserWidget::StaticClass, TEXT("UXYZUserWidget"), &Z_Registration_Info_UClass_UXYZUserWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXYZUserWidget), 3913664595U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUserWidget_h_1258442681(TEXT("/Script/XYZ"),
		Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUserWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZUserWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
