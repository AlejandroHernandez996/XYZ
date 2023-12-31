// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IntMatchStat.h"
#include "MatchStatType.h"
#include "NotficationType.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "XYZInputType.h"
#include "XYZInputMessage.h"
#include "XYZAnimMontageType.h"
#include "XYZPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxTriggeredEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionBoxReleasedEvent, float, x, float, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSelectionIdsEvent, const TArray<int32>&, SelectionActorIds, const int32&, SelectedResourceId, const int32&, SelectedEnemyId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlGroupEvent, const TArray<int32>&, ControlGroups);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLoadingScreenEvent, const TArray<FString>&, PlayerNames, const TArray<int32>&, Ratings, float, LoadPercentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChatEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotificationEvent, const FString&, NotificationString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMatchStatsEvent, const TArray<FIntMatchStat>&, MatchStatsTeam1, const TArray<FIntMatchStat>&, MatchStatsTeam2);

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

	UPROPERTY()
	class AXYZGameState* XYZGameState;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* CameraMovementAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<UInputAction*> CameraGroupInputActions;

	/** ADD TO SELECTION - QUEUE INPUT **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* OpenChatInputAction;
	UPROPERTY(BlueprintReadOnly)
	bool bIsChatting;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FChatEvent OnChatEvent;
	
	bool bPrimaryModifier;
	bool bSecondaryModifier;

	UPROPERTY(BlueprintReadOnly)
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
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FLoadingScreenEvent OnLoadingScreenEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FNotificationEvent OnNotificationEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FMatchStatsEvent OnMatchStatsEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bAllowMouseInput = true;

protected:
	virtual void BeginPlay();

	UFUNCTION()
	FVector SnapToGridCenter(const FVector& Location);
	virtual void Tick(float DeltaSeconds);

	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void OnInputStarted(EXYZInputType InputType);
	UFUNCTION()
	void OnInputTriggered(EXYZInputType InputType);
	UFUNCTION()
	void OnInputReleased(EXYZInputType InputType);

	UFUNCTION(BlueprintCallable)
	void OnControlGroupInputStarted(int32 ControlGroupIndex);
	UFUNCTION()
	void OnCameraGroupInputStarted(int32 CameraGroupIndex);
	UFUNCTION(BlueprintCallable)
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

	UPROPERTY()
	TMap<EXYZInputType, float> LastInputTime;
	UPROPERTY()
	TMap<int32, float> LastControlGroupInputTime;
	UPROPERTY()
	float DoubleInputThreshold = .30f;
	
	UPROPERTY()
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Match")
	int32 MatchStatus;
	UFUNCTION(Reliable, Client)
	void UpdateMatchStatus(int32 Status);
	void UpdateMatchStatus_Implementation(int32 Status);

	UFUNCTION(Reliable, Client)
	void SetVisibleEnemyActors(const TArray<int32>& VisibleActors, const TArray<int32>& NonVisibleActors);
	void SetVisibleEnemyActors_Implementation(const TArray<int32>& VisibleActors, const TArray<int32>& NonVisibleActors);
	
	UFUNCTION(Reliable, Client)
	void SendVisibilityGridCoords(const TArray<FIntVector2>& DeltaVisible, const TArray<FIntVector2>& DeltaDNonVisible);
	void SendVisibilityGridCoords_Implementation(const TArray<FIntVector2>& DeltaVisible, const TArray<FIntVector2>& DeltaNonVisible);

	UFUNCTION(Reliable, Client)
	void UpdateClientVisibility(const TArray<int32>& VisibleActors, const TArray<int32>& NonVisibleActors,const TArray<FIntVector2>& DeltaVisible, const TArray<FIntVector2>& DeltaNonVisible);
	void UpdateClientVisibility_Implementation(const TArray<int32>& VisibleActors, const TArray<int32>& NonVisibleActors,const TArray<FIntVector2>& DeltaVisible, const TArray<FIntVector2>& DeltaNonVisible);

	UPROPERTY()
	TArray<int32> VisibleEnemyActors;
	UPROPERTY()
	TArray<int32> NonVisibleEnemyActors;

	UPROPERTY()
	class AXYZFogOfWar* FogOfWar;
	UPROPERTY()
	class AXYZMinimapManager* MinimapManager;

	UFUNCTION()
	void UpdateVisibleActors();
	UFUNCTION()
	void UpdateMouseCursor();

	UFUNCTION(Reliable, Client)
	void UpdateLoadingScreen(const TArray<FString>& PlayerNames,const TArray<int32>& Ratings, const float LoadingPercentage);
	void UpdateLoadingScreen_Implementation(const TArray<FString>& PlayerNames,const TArray<int32>& Ratings, const float LoadingPercentage);

	UPROPERTY()
	bool bIsPlacingBuilding = false;
	UPROPERTY()
	class AXYZBuilding* PlacementBuilding;
	UPROPERTY()
	int32 WorkerAbilityIndex = -1;
	UPROPERTY()
	int32 WorkerActorId = -1;

	UFUNCTION()
	void ClearBuildingPlacement();

	UFUNCTION()
	FVector GetMouseToWorldPosition(APlayerController* PlayerController);

	UFUNCTION(Reliable, Client)
	void SendNotification(FNotificationPayload NotificationPayload);
	void SendNotification_Implementation(FNotificationPayload NotificationPayload);

	UFUNCTION(BlueprintCallable)
	void AttackMoveFromMinimap(FVector2D TargetLocation);

	UFUNCTION()
	bool CanPlaceBuilding(FVector CenterLocation, int32 GridSizeX, int32 GridSizeY);
	bool IsPointInBuildingGridArea(const FVector2D& Point, AXYZBuilding* Building);
	UPROPERTY()
	bool bIsBuildingPlaceable;
	
	UFUNCTION(BlueprintCallable)
	void MoveFromMinimap(FVector2D TargetLocation);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void CancelProductionAtIndex(int32 Index, int32 UActorId);
	void CancelProductionAtIndex_Implementation(int32 Index, int32 UActorId);

	UFUNCTION(Client, Reliable)
	void PlayAbilitySound(int32 ActorUID, int32 AbilityIndex);
	void PlayAbilitySound_Implementation(int32 ActorUID, int32 AbilityIndex);

	UPROPERTY()
	class AXYZAbilityMarker* ActiveAbilityMarker;
	UPROPERTY()
	class UXYZTargetAbility* ActiveTargetAbility;
	UPROPERTY()
	int32 ActiveAbilityIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	TArray<UMaterialInstance*> CloakedTeamColors;

	UFUNCTION(Client, Reliable)
	void CloakActor(AXYZActor* Actor);
	void CloakActor_Implementation(AXYZActor* Actor);

	UFUNCTION(Client, Reliable)
	void UncloakActor(AXYZActor* Actor);
	void UncloakActor_Implementation(AXYZActor* Actor);

	UFUNCTION(Client, Reliable)
	void DrawLine(FVector Start, FVector End, FColor Color);
	void DrawLine_Implementation(FVector Start, FVector End, FColor Color);

	UFUNCTION(Client, Reliable)
	void SendMatchStats(const TArray<FIntMatchStat>& Team1Stats, const TArray<FIntMatchStat>& Team2Stats);
	void SendMatchStats_Implementation(const TArray<FIntMatchStat>& Team1Stats, const TArray<FIntMatchStat>& Team2Stats);

	UPROPERTY()
	bool bHasHiddenEnemyBuildings;
};
