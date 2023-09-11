// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZPlayerController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AXYZActor;
enum class EXYZInputType : uint8;
struct FXYZInputMessage;
#ifdef XYZ_XYZPlayerController_generated_h
#error "XYZPlayerController.generated.h already included, missing '#pragma once' in XYZPlayerController.h"
#endif
#define XYZ_XYZPlayerController_generated_h

#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_16_DELEGATE \
XYZ_API void FSelectionBoxEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionBoxEvent, float x, float y);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_17_DELEGATE \
XYZ_API void FSelectionBoxTriggeredEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionBoxTriggeredEvent, float x, float y);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_18_DELEGATE \
XYZ_API void FSelectionBoxReleasedEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionBoxReleasedEvent, float x, float y);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_19_DELEGATE \
XYZ_API void FSelectionIdsEvent_DelegateWrapper(const FMulticastScriptDelegate& SelectionIdsEvent, TArray<int32> const& SelectionActorIds);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_SPARSE_DATA
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_RPC_WRAPPERS \
	virtual void XYZActorDestroyed_Implementation(int32 ActorUId); \
	virtual void QueueInput_Implementation(FXYZInputMessage const& InputMessage); \
 \
	DECLARE_FUNCTION(execXYZActorDestroyed); \
	DECLARE_FUNCTION(execQueueInput); \
	DECLARE_FUNCTION(execSelectActorFromPanel); \
	DECLARE_FUNCTION(execSelectActors); \
	DECLARE_FUNCTION(execOnControlGroupInputStarted); \
	DECLARE_FUNCTION(execOnInputReleased); \
	DECLARE_FUNCTION(execOnInputTriggered); \
	DECLARE_FUNCTION(execOnInputStarted); \
	DECLARE_FUNCTION(execGetMousePositionOnViewport);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execXYZActorDestroyed); \
	DECLARE_FUNCTION(execQueueInput); \
	DECLARE_FUNCTION(execSelectActorFromPanel); \
	DECLARE_FUNCTION(execSelectActors); \
	DECLARE_FUNCTION(execOnControlGroupInputStarted); \
	DECLARE_FUNCTION(execOnInputReleased); \
	DECLARE_FUNCTION(execOnInputTriggered); \
	DECLARE_FUNCTION(execOnInputStarted); \
	DECLARE_FUNCTION(execGetMousePositionOnViewport);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_ACCESSORS
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_CALLBACK_WRAPPERS
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAXYZPlayerController(); \
	friend struct Z_Construct_UClass_AXYZPlayerController_Statics; \
public: \
	DECLARE_CLASS(AXYZPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/XYZ"), NO_API) \
	DECLARE_SERIALIZER(AXYZPlayerController)


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_INCLASS \
private: \
	static void StaticRegisterNativesAXYZPlayerController(); \
	friend struct Z_Construct_UClass_AXYZPlayerController_Statics; \
public: \
	DECLARE_CLASS(AXYZPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/XYZ"), NO_API) \
	DECLARE_SERIALIZER(AXYZPlayerController)


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AXYZPlayerController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AXYZPlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AXYZPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AXYZPlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AXYZPlayerController(AXYZPlayerController&&); \
	NO_API AXYZPlayerController(const AXYZPlayerController&); \
public: \
	NO_API virtual ~AXYZPlayerController();


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AXYZPlayerController(AXYZPlayerController&&); \
	NO_API AXYZPlayerController(const AXYZPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AXYZPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AXYZPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AXYZPlayerController) \
	NO_API virtual ~AXYZPlayerController();


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_21_PROLOG
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_SPARSE_DATA \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_RPC_WRAPPERS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_ACCESSORS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_CALLBACK_WRAPPERS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_INCLASS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_SPARSE_DATA \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_ACCESSORS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_CALLBACK_WRAPPERS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_INCLASS_NO_PURE_DECLS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> XYZ_API UClass* StaticClass<class AXYZPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
