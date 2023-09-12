// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "XYZInputType.h"
#include "XYZInputMessage.h"
#include "XYZPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxTriggeredEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxReleasedEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectionIdsEvent, const TArray<int32>&, SelectionActorIds);

UCLASS()
class AXYZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AXYZPlayerController();

	int32 TeamId = 0;
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortInputThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float InputTriggeredCooldown = .25f;

	FTimerHandle InputTriggeredCooldownTimer;
	bool bCanInputRepeatWhileTriggered = true;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* MoveCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* AttackCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** SELECT BOX INPUT - SELECT SINGLE INPUT **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* PrimaryInputAction;

	/** MOVE - ATTACK**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SecondaryInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackMoveInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* StopInputAction;

	/** ADD TO SELECTION - QUEUE INPUT **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PrimaryModifierInputAction;

	/** SELECT ALL OF TYPE **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SecondaryModifierInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ClearSelectionInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TArray<UInputAction*> ControlGroupInputActions;


	bool bPrimaryModifier;
	bool bSecondaryModifier;
	bool bAttackModifier;
	bool bBlockPrimaryInputFlagForAttack;

	UFUNCTION()
	FVector2D GetMousePositionOnViewport();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D BoxSelectStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D BoxSelectEnd;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSelectionBoxEvent OnSelectionBox;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSelectionBoxTriggeredEvent OnSelectionBoxTriggered;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSelectionBoxReleasedEvent OnSelectionBoxReleased;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSelectionIdsEvent OnSelectionIdsEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bAllowMouseInput = true;

protected:
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);


	virtual void SetupInputComponent() override;
	
	/** Input handlers for SetDestination action. */
	UFUNCTION()
	void OnInputStarted(EXYZInputType InputType);
	UFUNCTION()
	void OnInputTriggered(EXYZInputType InputType);
	UFUNCTION()
	void OnInputReleased(EXYZInputType InputType);

	UFUNCTION()
	void OnControlGroupInputStarted(int32 ControlGroupIndex);

	UFUNCTION()
	void SelectActors(TArray<AXYZActor*> Actors);

	UFUNCTION(BlueprintCallable, Category = "UI")
		void SelectActorFromPanel(int32 UActorId);

	void CreateAndQueueInput(TArray<int32> _SelectedActors, int32 _XYZTargetActor, FVector _TargetLocation, EXYZInputType _InputType, bool _bQueueInput);
	UFUNCTION(Server, Reliable)
	void QueueInput(const FXYZInputMessage& InputMessage);
	void QueueInput_Implementation(const FXYZInputMessage& InputMessage);

	FHitResult WorldHit;
	bool bWorldHitSuccessful = false;

	// We look for the location in the world where the player has pressed the input
	FHitResult XYZActorHit;
	bool bXYZActorHitSuccessful = false;

private:
	UPROPERTY()
	class UXYZSelectionStructure* SelectionStructure;

	UPROPERTY()
	TMap<EXYZInputType, float> InputTriggeredTime;

	bool bBoxSelectFlag;

public:
	UFUNCTION(NetMulticast, Reliable)
		void XYZActorDestroyed(int32 ActorUId);
	void XYZActorDestroyed_Implementation(int32 ActorUId);

};


