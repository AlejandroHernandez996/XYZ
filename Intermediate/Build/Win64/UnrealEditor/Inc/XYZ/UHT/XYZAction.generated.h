// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZAction.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AXYZActor;
#ifdef XYZ_XYZAction_generated_h
#error "XYZAction.generated.h already included, missing '#pragma once' in XYZAction.h"
#endif
#define XYZ_XYZAction_generated_h

#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_SPARSE_DATA
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execIsFlaggedForDeuque); \
	DECLARE_FUNCTION(execCancelAction); \
	DECLARE_FUNCTION(execCompleteAction); \
	DECLARE_FUNCTION(execStartAction); \
	DECLARE_FUNCTION(execTryAction); \
	DECLARE_FUNCTION(execProcessAction); \
	DECLARE_FUNCTION(execInitialize);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execIsFlaggedForDeuque); \
	DECLARE_FUNCTION(execCancelAction); \
	DECLARE_FUNCTION(execCompleteAction); \
	DECLARE_FUNCTION(execStartAction); \
	DECLARE_FUNCTION(execTryAction); \
	DECLARE_FUNCTION(execProcessAction); \
	DECLARE_FUNCTION(execInitialize);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_ACCESSORS
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUXYZAction(); \
	friend struct Z_Construct_UClass_UXYZAction_Statics; \
public: \
	DECLARE_CLASS(UXYZAction, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/XYZ"), NO_API) \
	DECLARE_SERIALIZER(UXYZAction)


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUXYZAction(); \
	friend struct Z_Construct_UClass_UXYZAction_Statics; \
public: \
	DECLARE_CLASS(UXYZAction, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/XYZ"), NO_API) \
	DECLARE_SERIALIZER(UXYZAction)


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UXYZAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UXYZAction) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UXYZAction); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UXYZAction); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UXYZAction(UXYZAction&&); \
	NO_API UXYZAction(const UXYZAction&); \
public: \
	NO_API virtual ~UXYZAction();


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UXYZAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UXYZAction(UXYZAction&&); \
	NO_API UXYZAction(const UXYZAction&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UXYZAction); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UXYZAction); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UXYZAction) \
	NO_API virtual ~UXYZAction();


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_13_PROLOG
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_SPARSE_DATA \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_RPC_WRAPPERS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_ACCESSORS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_INCLASS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_SPARSE_DATA \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_ACCESSORS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_INCLASS_NO_PURE_DECLS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> XYZ_API UClass* StaticClass<class UXYZAction>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZAction_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
