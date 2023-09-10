// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "XYZActor.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AXYZActor;
class UXYZAction;
#ifdef XYZ_XYZActor_generated_h
#error "XYZActor.generated.h already included, missing '#pragma once' in XYZActor.h"
#endif
#define XYZ_XYZActor_generated_h

#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_SPARSE_DATA
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFindClosestActor); \
	DECLARE_FUNCTION(execQueueAction); \
	DECLARE_FUNCTION(execAttack);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFindClosestActor); \
	DECLARE_FUNCTION(execQueueAction); \
	DECLARE_FUNCTION(execAttack);


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_ACCESSORS
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAXYZActor(); \
	friend struct Z_Construct_UClass_AXYZActor_Statics; \
public: \
	DECLARE_CLASS(AXYZActor, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/XYZ"), NO_API) \
	DECLARE_SERIALIZER(AXYZActor) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		UActorId=NETFIELD_REP_START, \
		Health, \
		MaxHealth, \
		MoveSpeed, \
		BaseArmor, \
		AttackDamage, \
		AttackRate, \
		AttackRange, \
		NETFIELD_REP_END=AttackRange	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAXYZActor(); \
	friend struct Z_Construct_UClass_AXYZActor_Statics; \
public: \
	DECLARE_CLASS(AXYZActor, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/XYZ"), NO_API) \
	DECLARE_SERIALIZER(AXYZActor) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		UActorId=NETFIELD_REP_START, \
		Health, \
		MaxHealth, \
		MoveSpeed, \
		BaseArmor, \
		AttackDamage, \
		AttackRate, \
		AttackRange, \
		NETFIELD_REP_END=AttackRange	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AXYZActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AXYZActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AXYZActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AXYZActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AXYZActor(AXYZActor&&); \
	NO_API AXYZActor(const AXYZActor&); \
public: \
	NO_API virtual ~AXYZActor();


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AXYZActor(AXYZActor&&); \
	NO_API AXYZActor(const AXYZActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AXYZActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AXYZActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AXYZActor) \
	NO_API virtual ~AXYZActor();


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_12_PROLOG
#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_SPARSE_DATA \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_RPC_WRAPPERS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_ACCESSORS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_INCLASS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_SPARSE_DATA \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_ACCESSORS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_INCLASS_NO_PURE_DECLS \
	FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> XYZ_API UClass* StaticClass<class AXYZActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_OneDrive_Documents_Unreal_Projects_XYZ_Source_XYZ_XYZActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS