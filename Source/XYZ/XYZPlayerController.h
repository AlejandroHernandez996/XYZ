// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "XYZInputType.h"
#include "XYZInputMessage.h"
#include "XYZAnimMontageType.h"
#include "XYZPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxTriggeredEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxReleasedEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectionIdsEvent, const TArray<int32>&, SelectionActorIds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlGroupEvent, const TArray<int32>&, ControlGroups);

UCLASS()
class AXYZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AXYZPlayerController();
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 TeamId = -1;
	bool bMoveCameraFlag;
	FVector CameraLocation;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Disconnect();
	void Disconnect_Implementation();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void FocusCameraOnLocation(FVector Location);
	void FocusCameraOnLocation_Implementation(FVector Location);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* HoldInputAction;

	/** ADD TO SELECTION - QUEUE INPUT **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PrimaryModifierInputAction;

	/** SELECT ALL OF TYPE **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SecondaryModifierInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ClearSelectionInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CycleSelectionInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TArray<UInputAction*> ControlGroupInputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TArray<UInputAction*> AbilityInputActions;

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

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FControlGroupEvent OnControlGroupEvent;

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
		void OnAbilityInputStarted(int32 AbilityIndex);
	UFUNCTION()
		void OnCycleSelectionInputStarted();

	UFUNCTION()
	void SelectActors(TArray<AXYZActor*> Actors);

	UFUNCTION(BlueprintCallable, Category = "UI")
		void SelectActorFromPanel(int32 UActorId);
	UFUNCTION(BlueprintCallable, Category = "UI")
		class AXYZActor* GetActiveSelectedActor();
	void CreateAndQueueInput(TArray<int32> _SelectedActors, int32 _XYZTargetActor, FVector _TargetLocation, EXYZInputType _InputType, bool _bQueueInput);
	UFUNCTION(Server, Reliable)
	void QueueInput(const FXYZInputMessage& InputMessage);
	void QueueInput_Implementation(const FXYZInputMessage& InputMessage);

	FHitResult WorldHit;
	bool bWorldHitSuccessful = false;

	FHitResult XYZActorHit;
	bool bXYZActorHitSuccessful = false;

private:
	UPROPERTY()
	TMap<EXYZInputType, float> InputTriggeredTime;

	bool bBoxSelectFlag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class AXYZCameraController* CameraController;

public:
	UPROPERTY(BlueprintReadOnly)
		class UXYZSelectionStructure* SelectionStructure;

	UFUNCTION(Client, Reliable)
		void XYZActorDestroyed(int32 ActorUId);
	void XYZActorDestroyed_Implementation(int32 ActorUId);

	UFUNCTION(Server, Reliable)
		void PingServerGameIsLoaded();
	void PingServerGameIsLoaded_Implementation();
	bool bPingedGameLoaded;

	UFUNCTION(Client, Reliable)
		void PlayAnimationMontage(EXYZAnimMontageType AnimationType, AXYZActor* Actor);
	void PlayAnimationMontage_Implementation(EXYZAnimMontageType AnimationType, AXYZActor* Actor);

	void OnNetCleanup(UNetConnection* Connection) override;
};


