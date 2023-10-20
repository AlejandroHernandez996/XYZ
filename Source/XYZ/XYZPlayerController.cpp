// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYZPlayerController.h"

#include "GameFramework/Pawn.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "XYZActor.h"
#include "XYZGameMode.h"
#include "XYZGameState.h"
#include "DrawDebugHelpers.h"
#include "XYZSelectionStructure.h"
#include "Kismet/GameplayStatics.h" 
#include "XYZHUD.h"
#include "EnhancedInputSubsystems.h"
#include "XYZCameraController.h"
#include "XYZResourceActor.h"
#include "EngineUtils.h"
#include "XYZBuilding.h"
#include "XYZFogOfWar.h"
#include "XYZMinimapManager.h"
#include "XYZSoundManager.h"
#include "XYZWorkerAbility.h"
#include "Components/CapsuleComponent.h"
#include "Components/LineBatchComponent.h"
#include "Net/UnrealNetwork.h"

AXYZPlayerController::AXYZPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
		EnumValue <= static_cast<int32>(EXYZInputType::STOP);
		EnumValue++)
	{
		InputTriggeredTime.Add(static_cast<EXYZInputType>(EnumValue), 0.0f);
	}
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
		EnumValue <= static_cast<int32>(EXYZInputType::STOP);
		EnumValue++)
	{
		LastInputTime.Add(static_cast<EXYZInputType>(EnumValue), 0.0f);
	}
	ShortInputThreshold = .25f;
	PrimaryActorTick.bCanEverTick = true;
}

void AXYZPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SelectionStructure = NewObject<UXYZSelectionStructure>(this, UXYZSelectionStructure::StaticClass(), "SelectionStructure");
	SelectionStructure->InitControlGroups(ControlGroupInputActions.Num());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	for (TActorIterator<AXYZCameraController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		CameraController = *ActorItr;
		if(CameraController)
		{
			CameraController->XYZPlayerController = this;
		}
	}

}

FVector AXYZPlayerController::SnapToGridCenter(const FVector& Location)
{
	float gridSize = 100.0f;
	FVector adjustedLocation = Location;

	int32 GridSizeX = PlacementBuilding->GridSize.X;
	int32 GridSizeY = PlacementBuilding->GridSize.Y;
	
	if(GridSizeX % 2 == 0)
		adjustedLocation.X -= gridSize / 2;

	if(GridSizeY % 2 == 0)
		adjustedLocation.Y -= gridSize / 2;
    
	int32 gridIndexX = FMath::FloorToInt(adjustedLocation.X / gridSize);
	int32 gridIndexY = FMath::FloorToInt(adjustedLocation.Y / gridSize);
    
	float centerX = (gridIndexX * gridSize) + ((GridSizeX % 2 == 0) ? 0 : gridSize / 2);
	float centerY = (gridIndexY * gridSize) + ((GridSizeY % 2 == 0) ? 0 : gridSize / 2);

	return FVector(centerX, centerY, Location.Z);
}

void AXYZPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if(!XYZGameState)
	{
		XYZGameState = GetWorld()->GetGameState<AXYZGameState>();
	}
	if(GetLocalRole() == ROLE_Authority) return;
	
	UpdateVisibleActors();
	UpdateMouseCursor();
	
	float x, y;
	if (!GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y)) {
		OnSelectionBoxReleased.Broadcast(0, 0);
	}

	bWorldHitSuccessful = GetHitResultAtScreenPosition(GetMousePositionOnViewport(), ECC_WorldStatic, true, WorldHit);
	bXYZActorHitSuccessful = GetHitResultAtScreenPosition(GetMousePositionOnViewport(), ECC_WorldStatic, true, XYZActorHit);
	if(!Cast<AXYZActor>(XYZActorHit.GetActor()))
	{
		FVector MouseWorldLocation, MouseWorldDirection;
		DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		TArray<FHitResult> HitResults;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		CollisionParams.AddIgnoredActor(CameraController);

		FVector StartLocation = MouseWorldLocation;
		FVector EndLocation = StartLocation + MouseWorldDirection * 10000.0f;

		ECollisionChannel TraceChannel = ECC_Pawn;

		if (GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, EndLocation, TraceChannel, CollisionParams))
		{
			for (const FHitResult& HitResult : HitResults)
			{
				AActor* HitActor = HitResult.GetActor();
				if (HitActor && HitActor->IsA(AXYZActor::StaticClass()))
				{
					AXYZActor* XYZActor = Cast<AXYZActor>(HitActor);
					if (XYZActor)
					{
						XYZActorHit = HitResult;
						bXYZActorHitSuccessful = true;
						break;
					}
				}
			}
		}
	}
	
	if(CameraController && bMoveCameraFlag)
	{
		FVector LocationWithOffset = FVector(CameraLocation.X, CameraLocation.Y, CameraController->GetActorLocation().Z) + FVector(-250, 50,0.0f);
		CameraController->SetActorLocation(LocationWithOffset);
		bMoveCameraFlag = false;
	}
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
			EnumValue <= static_cast<int32>(EXYZInputType::STOP);
			EnumValue++)
	{
		InputTriggeredTime[static_cast<EXYZInputType>(EnumValue)] += DeltaTime;
	}
	for (int32 EnumValue = static_cast<int32>(EXYZInputType::PRIMARY_INPUT);
			EnumValue <= static_cast<int32>(EXYZInputType::STOP);
			EnumValue++)
	{
		LastInputTime[static_cast<EXYZInputType>(EnumValue)] += DeltaTime;
	}
	for(int32 i = 0;i < LastControlGroupInputTime.Num();i++)
	{
		LastControlGroupInputTime[i] += DeltaTime;
	}
	if(!FogOfWar)
	{
		for (TActorIterator<AXYZFogOfWar> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			FogOfWar = *ActorItr;
		}
	}
	if(!MinimapManager)
	{
		for (TActorIterator<AXYZMinimapManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			MinimapManager = *ActorItr;
		}
	}
	
	bool bNotPlacingBuildingAndTemplate = !bIsPlacingBuilding && PlacementBuilding;
	bool bActiveActorDoesNotMatchWorkerId = !SelectionStructure ? false : SelectionStructure->IsEmpty() || SelectionStructure->ActiveActor != WorkerActorId;
	if(bNotPlacingBuildingAndTemplate || bActiveActorDoesNotMatchWorkerId)
	{
		ClearBuildingPlacement();
	}
	if(PlacementBuilding)
	{
		FVector NewLocation = GetMouseToWorldPosition(this);

		NewLocation = SnapToGridCenter(NewLocation);

		UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(PlacementBuilding->GetComponentByClass(UCapsuleComponent::StaticClass()));
		if(Capsule)
		{
			NewLocation.Z += Capsule->GetScaledCapsuleHalfHeight();
		}

		PlacementBuilding->SetActorLocation(NewLocation);

		bIsBuildingPlaceable = CanPlaceBuilding(NewLocation, PlacementBuilding->GridSize.X, PlacementBuilding->GridSize.Y);

		TArray<UStaticMeshComponent*> ChildMeshes;
		PlacementBuilding->GetComponents<UStaticMeshComponent>(ChildMeshes);

		int32 MaterialIndex = bIsBuildingPlaceable ? 0 : 1;
		for(UStaticMeshComponent* MeshComp : ChildMeshes)
		{
			if(PlacementBuilding->PlacementMaterials.IsValidIndex(MaterialIndex))
			{
				MeshComp->SetMaterial(0, PlacementBuilding->PlacementMaterials[MaterialIndex]);
			}
		}
	}

	if(!HasAuthority() && XYZGameState)
	{
		TArray<AXYZActor*> Actors;
		XYZGameState->ActorsByUID.GenerateValueArray(Actors);
		ULineBatchComponent* LineBatcher = GetWorld()->ForegroundLineBatcher;
		for(AXYZActor* Actor : Actors)
		{
			if(Actor && Actor->bIsFlying && Actor->bIsVisible && Actor->State != EXYZUnitState::DEAD)
			{
				FColor LineColor = TeamId == Actor->TeamId ? FColor::Green : FColor::Red;

				FVector StartLocation = Actor->GetActorLocation() + FVector::DownVector * Actor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
				FVector EndLocation = StartLocation;
				EndLocation.Z = 0.0f;
        
				if (LineBatcher)
				{
					float Radius = Actor->GetCapsuleComponent()->GetScaledCapsuleRadius();
					LineBatcher->DrawLine(EndLocation, StartLocation, LineColor, SDPG_World, 1.0f, .1f);
					FVector CircleCenter = Actor->GetActorLocation() + FVector::DownVector * Actor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
					FVector XAxisDirection = FVector::RightVector;
					FVector YAxisDirection = FVector::ForwardVector;
					int NumSides = 32;
					switch(Actor->CurrentDecal)
					{
					case EXYZDecalType::FRIENDLY:
						LineColor = FColor::Green;
						break;
					case EXYZDecalType::ENEMY:
						LineColor = FColor::Red;
						break;
					case EXYZDecalType::NEUTRAL:
					default:
						LineColor = FColor::White;
						break;
					}
					LineBatcher->DrawCircle(CircleCenter, XAxisDirection, YAxisDirection, LineColor, Radius, NumSides, SDPG_MAX);
				}
			}
			if(Actor &&
				Actor->bIsVisible &&
				Actor->State != EXYZUnitState::DEAD &&
				Actor->TeamId == TeamId &&
				Actor->CurrentDecal != EXYZDecalType::NEUTRAL &&
				Actor->IsA(AXYZUnit::StaticClass()) &&
				!Actor->PathingPoints.IsEmpty() &&
				Actor->PathingPoints.Num() == Actor->PathingPointsColors.Num() &&
				Actor->PathingPointsColors.Num() == Actor->PathingPointsShowFlag.Num())
			{
				FVector LastPathingPoint = Actor->PathingPoints[0];
				for(int i = 0;i < Actor->PathingPoints.Num();i++)
				{
					if(Actor->PathingPointsShowFlag[i])
					{
						FVector XAxisDirection = FVector::RightVector;
						FVector YAxisDirection = FVector::ForwardVector;
						int NumSides = 32;
						LineBatcher->DrawLine(LastPathingPoint, Actor->PathingPoints[i], Actor->PathingPointsColors[i], SDPG_MAX, 2.0f, .1f);
						LineBatcher->DrawCircle(Actor->PathingPoints[i], XAxisDirection, YAxisDirection, Actor->PathingPointsColors[i], 10.0f, NumSides, SDPG_MAX);
						LastPathingPoint = Actor->PathingPoints[i];
					}
				}
			}
		}

		
	}
}

void AXYZPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::PRIMARY_INPUT);
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::PRIMARY_INPUT);
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::PRIMARY_INPUT);
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::PRIMARY_INPUT);

		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::SECONDARY_INPUT);
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::SECONDARY_INPUT);
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::SECONDARY_INPUT);
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::SECONDARY_INPUT);

		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::ATTACK_MOVE);
		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::ATTACK_MOVE);
		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::ATTACK_MOVE);
		EnhancedInputComponent->BindAction(AttackMoveInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::ATTACK_MOVE);

		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::STOP);
		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::STOP);
		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::STOP);
		EnhancedInputComponent->BindAction(StopInputAction, ETriggerEvent::Canceled, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::STOP);

		EnhancedInputComponent->BindAction(HoldInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::HOLD);

		EnhancedInputComponent->BindAction(PrimaryModifierInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::PRIMARY_MOD);
		EnhancedInputComponent->BindAction(PrimaryModifierInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::PRIMARY_MOD);

		EnhancedInputComponent->BindAction(SecondaryModifierInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::SECONDARY_MOD);
		EnhancedInputComponent->BindAction(SecondaryModifierInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::SECONDARY_MOD);

		EnhancedInputComponent->BindAction(ClearSelectionInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::CLEAR);
		EnhancedInputComponent->BindAction(CycleSelectionInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnCycleSelectionInputStarted);

		for (int32 i = 0; i < ControlGroupInputActions.Num(); i++) {
			EnhancedInputComponent->BindAction(ControlGroupInputActions[i], ETriggerEvent::Started, this, &AXYZPlayerController::OnControlGroupInputStarted, i);
			LastControlGroupInputTime.Add(i,0.0f);
		}

		for (int32 i = 0; i < CameraGroupInputActions.Num(); i++) {
			EnhancedInputComponent->BindAction(CameraGroupInputActions[i], ETriggerEvent::Started, this, &AXYZPlayerController::OnCameraGroupInputStarted, i);
		}

		for (int32 i = 0; i < AbilityInputActions.Num(); i++) {
			EnhancedInputComponent->BindAction(
				AbilityInputActions[i],
				ETriggerEvent::Started,
				this,
				&AXYZPlayerController::OnAbilityInputStarted,
				i);
		}

		EnhancedInputComponent->BindAction(CameraMovementAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::CAMERA);
		EnhancedInputComponent->BindAction(CameraMovementAction, ETriggerEvent::Triggered, this, &AXYZPlayerController::OnInputTriggered, EXYZInputType::CAMERA);
		EnhancedInputComponent->BindAction(CameraMovementAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::CAMERA);

		EnhancedInputComponent->BindAction(OpenChatInputAction, ETriggerEvent::Started, this, &AXYZPlayerController::OnInputStarted, EXYZInputType::CHAT);
		EnhancedInputComponent->BindAction(OpenChatInputAction, ETriggerEvent::Completed, this, &AXYZPlayerController::OnInputReleased, EXYZInputType::CHAT);
	}
}

void AXYZPlayerController::OnControlGroupInputStarted(int32 ControlGroupIndex) {
	if(PlacementBuilding)
	{
		ClearBuildingPlacement();
	}
	bool bDoubleInput = LastControlGroupInputTime[ControlGroupIndex] <= DoubleInputThreshold;
	LastControlGroupInputTime[ControlGroupIndex] = 0.0f;
	if (bPrimaryModifier) {
		SelectionStructure->AddToControlGroup(ControlGroupIndex);
	}
	else if (bSecondaryModifier) {
		SelectionStructure->SetControlGroup(ControlGroupIndex);
	}
	else {
		SelectionStructure->SelectControlGroup(ControlGroupIndex);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
		if(bDoubleInput && !SelectionStructure->IsEmpty())
		{
			FVector TargetActorLocation = SelectionStructure->ToArray()[0]->GetActorLocation();
			CameraController->SetActorLocation(FVector(TargetActorLocation.X, TargetActorLocation.Y, CameraController->GetActorLocation().Z) + FVector(-250.0f, 50.0f, 0.0f));
		}
	}
	TArray<int32> ControlGroups;
	for (TSortedMap<int32, TMap<int32, AXYZActor*>> ControlGroup : SelectionStructure->ControlGroups) {
		ControlGroups.Add(ControlGroup.Num());
	}
	OnControlGroupEvent.Broadcast(ControlGroups);
}

void AXYZPlayerController::OnCameraGroupInputStarted(int32 CameraGroupIndex) {
	if(CameraController)
	{
		if(bSecondaryModifier)
		{
			CameraController->SaveCameraLocation(CameraGroupIndex);
		}else
		{
			CameraController->JumpToCameraLocation(CameraGroupIndex);
		}
	}
}

void AXYZPlayerController::OnAbilityInputStarted(int32 AbilityIndex) {
	if(PlacementBuilding)
	{
		ClearBuildingPlacement();
	}
	if (SelectionStructure->IsEmpty()) return;

	AXYZActor* Actor = XYZGameState->GetActorById(SelectionStructure->ActiveActor);
	if(!Actor || !Actor->Abilities.IsValidIndex(AbilityIndex) || !Actor->Abilities[AbilityIndex]) return;
	if(!XYZGameState->DoesAbilityHaveRequirements(Actor->Abilities[AbilityIndex], TeamId)) return;

	AXYZWorker* ActiveWorker = Cast<AXYZWorker>(XYZGameState->GetActorById(SelectionStructure->ActiveActor));
	UXYZWorkerAbility* WorkerAbility = nullptr;
	if(ActiveWorker && AbilityIndex < ActiveWorker->Abilities.Num())
	{
		WorkerAbility = Cast<UXYZWorkerAbility>(ActiveWorker->Abilities[AbilityIndex]);
	}
	
	if(ActiveWorker &&  WorkerAbility)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlacementBuilding = GetWorld()->SpawnActor<AXYZBuilding>(
			WorkerAbility->PlacementTemplate,
			FVector(GetMouseToWorldPosition(this)),
				FRotator(0, 0, 0),
				SpawnParams);
		TArray<UStaticMeshComponent*> MeshComponents;
		PlacementBuilding->GetComponents<UStaticMeshComponent*>(MeshComponents);
		for(UStaticMeshComponent* MeshComponent : MeshComponents)
		{
			if(MeshComponent->GetName().Equals("Plane"))
			{
				MeshComponent->SetWorldScale3D(FVector(PlacementBuilding->GridSize.X * .781, PlacementBuilding->GridSize.Y * .781, .25f));
				MeshComponent->SetRelativeLocation(FVector(0.f,0.f,-1.0f * PlacementBuilding->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + .5f));
			}
		}
		bIsPlacingBuilding = true;
		WorkerAbilityIndex = AbilityIndex;
		WorkerActorId = SelectionStructure->ActiveActor;
		return;
	}
	
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	if(HitActor && !HitActor->bIsVisible)
	{
		HitActor = nullptr;
	}
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
	FXYZInputMessage AbilityInput = FXYZInputMessage(SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, EXYZInputType::ABILITY, bPrimaryModifier);
	AbilityInput.AbilityIndex = AbilityIndex;
	AbilityInput.ActiveActorId = SelectionStructure->ActiveActor;
	QueueInput(AbilityInput);
}

void AXYZPlayerController::OnCycleSelectionInputStarted() {
	SelectionStructure->CycleSelection();
}

void AXYZPlayerController::OnInputStarted(EXYZInputType InputType)
{
	if(PlacementBuilding && InputType != EXYZInputType::PRIMARY_INPUT && InputType != EXYZInputType::PRIMARY_MOD)
	{
		ClearBuildingPlacement();
	}
	FXYZInputMessage InputMessage;
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	if(HitActor && !HitActor->bIsVisible)
	{
		HitActor = nullptr;
	}
	int32 XYZActorHitId = bXYZActorHitSuccessful && HitActor ? HitActor->UActorId : -1;
	switch (InputType) {
		case EXYZInputType::PRIMARY_INPUT:
			UE_LOG(LogTemp, Warning, TEXT("Primary Input Pressed"));
			if (!bAllowMouseInput) return;
			if (bAttackModifier) {
				if (SelectionStructure->IsEmpty()) return;
				bAttackModifier = false;
				bBlockPrimaryInputFlagForAttack = true;
				CreateAndQueueInput(SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, EXYZInputType::ATTACK_MOVE, bPrimaryModifier);
				if (!HitActor || (SelectionStructure->Num == 1 && SelectionStructure->ToActorIdArray()[0] == XYZActorHitId)) {
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, AttackCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
				}
				break;
			}
			if(bIsPlacingBuilding && PlacementBuilding && WorkerAbilityIndex != -1 && WorkerActorId != -1)
			{
				if(bIsBuildingPlaceable)
				{
					FXYZInputMessage AbilityInput = FXYZInputMessage(SelectionStructure->ToActorIdArray(), -1, PlacementBuilding->GetActorLocation(), EXYZInputType::ABILITY, bPrimaryModifier);
					AbilityInput.AbilityIndex = WorkerAbilityIndex;
					AbilityInput.ActiveActorId = WorkerActorId;
					QueueInput(AbilityInput);
				}
				PlacementBuilding->Destroy();
				break;
			}
			BoxSelectStart = GetMousePositionOnViewport();
			GetHUD<AXYZHUD>()->bSelectActors = true;
			GetHUD<AXYZHUD>()->BoxStart = BoxSelectStart;
			GetHUD<AXYZHUD>()->BoxEnd = BoxSelectStart;
			OnSelectionBox.Broadcast(BoxSelectStart.X, BoxSelectStart.Y);
			bBoxSelectFlag = true;
			if (CameraController) {
				CameraController->bBlockMovementFlag = true;
			}
			break;
		case EXYZInputType::SECONDARY_INPUT:
			if (!bAllowMouseInput) return;
			bAttackModifier = false;
			if (SelectionStructure->IsEmpty()) return;
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), XYZActorHitId, WorldHit.Location, InputType, bPrimaryModifier);
			if (!HitActor || (SelectionStructure->Num == 1 && SelectionStructure->ToActorIdArray()[0] == XYZActorHitId)) {
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MoveCursor, WorldHit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}
			break;
		case EXYZInputType::PRIMARY_MOD:
			bPrimaryModifier = true;
			break;
		case EXYZInputType::SECONDARY_MOD:
			bSecondaryModifier = true;
			break;
		case EXYZInputType::ATTACK_MOVE:
			if (!SelectionStructure->IsEmpty()) {
				bAttackModifier = true;
			}
			break;
		case EXYZInputType::STOP:
			bAttackModifier = false;
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, false);
			break;
		case EXYZInputType::HOLD:
			bAttackModifier = false;
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), -1, WorldHit.Location, InputType, false);
			break;
		case EXYZInputType::CLEAR:
			SelectionStructure->Empty();
			OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
			break;
		case EXYZInputType::CAMERA:
			if(CameraController)
			{
				CameraController->StartDragMovement();
			}
			break;
		case EXYZInputType::CHAT:
			bIsChatting = !bIsChatting;
			OnChatEvent.Broadcast();
			break;
	}
}

void AXYZPlayerController::OnInputTriggered(EXYZInputType InputType)
{
	if (InputType == EXYZInputType::PRIMARY_INPUT) {
		if(bIsPlacingBuilding)
		{
			return;
		}
		BoxSelectEnd = GetMousePositionOnViewport();
		GetHUD<AXYZHUD>()->BoxEnd = BoxSelectEnd;
	}
	
	if (InputTriggeredTime[InputType] <= ShortInputThreshold) {
	}

	if (!bCanInputRepeatWhileTriggered && InputType != EXYZInputType::PRIMARY_INPUT) return;
	bCanInputRepeatWhileTriggered = false;
	GetWorld()->GetTimerManager().SetTimer(InputTriggeredCooldownTimer, [this]() {
		bCanInputRepeatWhileTriggered = true;
		}, InputTriggeredCooldown, false);

	switch (InputType) {
	case EXYZInputType::PRIMARY_INPUT:
		if (!bAllowMouseInput) return;
		OnSelectionBoxTriggered.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		break;
	case EXYZInputType::ATTACK_MOVE:
		bAttackModifier = !SelectionStructure->IsEmpty();
		break;
	case EXYZInputType::CAMERA:
		if(CameraController)
		{
			//CameraController->DragMove();
		}
		break;
	}
}

void AXYZPlayerController::OnInputReleased(EXYZInputType InputType)
{
	FHitResult BoxHitStart, BoxHitEnd;
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	if(HitActor && !HitActor->bIsVisible)
	{
		HitActor = nullptr;
	}
	InputTriggeredTime[InputType] = 0.0f;
	bool bDoubleInput = LastInputTime[InputType] <= DoubleInputThreshold;
	LastInputTime[InputType] = 0.0f;
	switch (InputType) {
	case EXYZInputType::PRIMARY_MOD:
		UE_LOG(LogTemp, Warning, TEXT("Primary Mod Released"));
		bPrimaryModifier = false;
		break;
	case EXYZInputType::SECONDARY_MOD:
		bSecondaryModifier = false;
		break;
	case EXYZInputType::PRIMARY_INPUT:
		UE_LOG(LogTemp, Warning, TEXT("Primary Input Released"));
		if(bIsPlacingBuilding)
		{
			ClearBuildingPlacement();
			return;
		}
		if(bBlockPrimaryInputFlagForAttack)
		{
			bBlockPrimaryInputFlagForAttack = false;
			break;
		}
		if (!bAllowMouseInput || !bBoxSelectFlag) break;
		if (FVector2D::Distance(BoxSelectStart, BoxSelectEnd) < 25.0f && bXYZActorHitSuccessful){
			if (HitActor) {
				if (bSecondaryModifier || bDoubleInput) {
					TArray<AXYZActor*> SelectedActors = GetHUD<AXYZHUD>()->SelectedActors;
					SelectedActors.RemoveAll([&](AXYZActor* Actor)
						{
							if (Actor)
							{
								return Actor->TeamId != TeamId;
							}
							return true;
						});
					if (SelectedActors.Num() > 0) {
						AXYZActor* SelectedActor = SelectedActors[0];
						if (SelectedActor) {
							TArray<AXYZActor*> AllMatchingSelectedActorOnScreen = GetHUD<AXYZHUD>()->AllActorsOnScreen;
							AllMatchingSelectedActorOnScreen.RemoveAll([&](AXYZActor* Actor)
								{
									if (Actor)
									{
										return Actor->TeamId != TeamId || Actor->ActorId != SelectedActor->ActorId;
									}
									return true;
								});
							if (AllMatchingSelectedActorOnScreen.Num() > 0) {
								SelectActors(AllMatchingSelectedActorOnScreen);
							}
						}
					}
					GetHUD<AXYZHUD>()->AllActorsOnScreen.Empty();
				}else
				{
					SelectActors({ HitActor });
				}
			}
		}
		else {
			SelectActors(GetHUD<AXYZHUD>()->SelectedActors);
		}
		bBoxSelectFlag = false;
		GetHUD<AXYZHUD>()->bSelectActors = false;
		if (CameraController) {
			CameraController->bBlockMovementFlag = false;
		}
		OnSelectionBoxTriggered.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		OnSelectionBoxReleased.Broadcast(BoxSelectEnd.X, BoxSelectEnd.Y);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
		break;
	case EXYZInputType::ATTACK_MOVE:
		break;
	case EXYZInputType::CAMERA:
		if(CameraController)
		{
			CameraController->EndDragMovement();
		}
		break;
	}
}

void AXYZPlayerController::SelectActors(TArray<AXYZActor*> _XYZActors){
	TSet<AXYZActor*> XYZActorsSet = TSet<AXYZActor*>(_XYZActors);
	TArray<AXYZActor*> XYZActors = XYZActorsSet.Array();
	XYZActors.RemoveAll([&](AXYZActor* Actor) {
		return Actor->Health <= 0.0f;
		});
	if (XYZActors.IsEmpty()) {
		return;
	}

	if (XYZActors.Num() == 1 && XYZActors[0]->IsA(AXYZResourceActor::StaticClass())) {
		SelectionStructure->SelectResource(XYZActors[0]);
		return;
	}

	if (XYZActors.Num() == 1 && XYZActors[0]->TeamId != TeamId) {
		SelectionStructure->SelectEnemyActor(XYZActors[0]);
		return;
	}
	XYZActors.RemoveAll([&](AXYZActor* Actor) {
		return Actor->IsA(AXYZResourceActor::StaticClass());
		});
	bool bSelectionOnlyBuildings = true;
	for (AXYZActor* Actor : XYZActors) {
		bSelectionOnlyBuildings = bSelectionOnlyBuildings && Actor->IsA(AXYZBuilding::StaticClass());
	}
	if (!bSelectionOnlyBuildings) {
		XYZActors.RemoveAll([&](AXYZActor* Actor) {
			return Actor->IsA(AXYZBuilding::StaticClass());
			});
	}
	TArray<AXYZActor*> OwnedXYZActors;
	for (auto XYZActor : XYZActors) {
		if (XYZActor->TeamId == TeamId) {
			OwnedXYZActors.Add(XYZActor);
		}
	}

	if (OwnedXYZActors.Num() == 1 && SelectionStructure->Contains(OwnedXYZActors[0]) && bPrimaryModifier) {
		SelectionStructure->Remove(OwnedXYZActors[0]);
		return;
	}

	if (bPrimaryModifier) {
		bool bInSelection = true;
		for (AXYZActor* XYZActor : OwnedXYZActors) {
			bInSelection = bInSelection && SelectionStructure->Contains(XYZActor);
		}
		if (bInSelection && OwnedXYZActors.Num() != SelectionStructure->ToArray().Num()) {
			SelectionStructure->Remove(OwnedXYZActors);
		}
		else {
			SelectionStructure->Add(OwnedXYZActors);
		}
	} 
	else {
		SelectionStructure->Empty();
		SelectionStructure->Add(OwnedXYZActors);
	}
}

FVector2D AXYZPlayerController::GetMousePositionOnViewport()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0); // Change 0 to the appropriate player index
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

void AXYZPlayerController::CreateAndQueueInput(TArray<int32> _SelectedActors, int32 _XYZTargetActor, FVector _TargetLocation, EXYZInputType _InputType, bool _bQueueInput) {
	QueueInput(FXYZInputMessage(_SelectedActors, _XYZTargetActor, _TargetLocation, _InputType, _bQueueInput));
}
void AXYZPlayerController::QueueInput_Implementation(const FXYZInputMessage& InputMessage) {
	if (GetLocalRole() != ROLE_Authority) return;
	AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();
	TMap<int32, AXYZActor*> ActorsByUId = XYZGameState->ActorsByUID;
	for (int32 UActorId : InputMessage.SelectedActors) {
		if (!ActorsByUId.Contains(UActorId)) {
			return;
		}
		if (ActorsByUId[UActorId]->TeamId != TeamId) {
			return;
		}
	}
	GameMode->QueueInput(InputMessage);
}

void AXYZPlayerController::SelectActorFromPanel(int32 UActorId) {
	if (XYZGameState->ActorsByUID.Contains(UActorId)) {
		SelectActors({ XYZGameState->ActorsByUID[UActorId]});
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());
	}
}

void AXYZPlayerController::XYZActorDestroyed_Implementation(int32 ActorUId) {
	if(!XYZGameState) return;
	if (XYZGameState->ActorsByUID.Contains(ActorUId)) {
		AXYZActor* Actor = XYZGameState->ActorsByUID[ActorUId];
		if (!Actor) return;
		USkeletalMeshComponent* Ragdoll = Actor->GetMesh();
		Ragdoll->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		Ragdoll->SetCollisionProfileName("Ragdoll");
		Ragdoll->SetSimulatePhysics(true);
		FVector ForceDirection = FVector(0, 0, 6000);
		Ragdoll->AddForce(ForceDirection);
		Actor->ShowDecal(false, EXYZDecalType::NEUTRAL);
		if (SelectionStructure->Contains(ActorUId)) {
			SelectionStructure->Remove(ActorUId);
		}
		SelectionStructure->RemoveFromControlGroups(ActorUId, Actor->ActorId);
		OnSelectionIdsEvent.Broadcast(SelectionStructure->ToActorIdArray());

		TArray<int32> ControlGroups;
		for (TSortedMap<int32, TMap<int32, AXYZActor*>> ControlGroup : SelectionStructure->ControlGroups) {
			ControlGroups.Add(ControlGroup.Num());
		}
		OnControlGroupEvent.Broadcast(ControlGroups);
		XYZGameState->ActorsByUID.Remove(ActorUId);

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
			{
				if (Cast<USkeletalMeshComponent>(SceneComponent))
				{
					continue;
				}
				SceneComponent->SetVisibility(false);
			}
		}

	}
	
}
void AXYZPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXYZPlayerController, TeamId);
}

void AXYZPlayerController::Disconnect_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "DISCONNECTED FROM MATCH");
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("MainMenuMap")));
}

void AXYZPlayerController::FocusCameraOnLocation_Implementation(FVector Location)
{
	if(HasAuthority()) return;
	bMoveCameraFlag = true;
	CameraLocation =Location; 
}

void AXYZPlayerController::PingServerGameIsLoaded_Implementation() {
	XYZGameState->bClientLoaded = true;
}

AXYZActor* AXYZPlayerController::GetActiveSelectedActor() {
	AXYZActor* Result = nullptr;
	TArray<int32> ActiveActorIds = SelectionStructure->GetActiveActorIds();
	if (!ActiveActorIds.IsEmpty() && XYZGameState->ActorsByUID.Contains(ActiveActorIds[0])) {
		Result = XYZGameState->ActorsByUID[ActiveActorIds[0]];
	}
	return Result;
}

void AXYZPlayerController::PlayAnimationMontage_Implementation(EXYZAnimMontageType AnimType, AXYZActor* Actor) {
	if (Actor && Actor->AnimMontageMap.Contains(AnimType)) {
		Actor->PlayAnimationMontage(AnimType);
	}
}

void AXYZPlayerController::OnNetCleanup(UNetConnection* Connection)
{
	if (GetLocalRole() == ROLE_Authority && PlayerState != NULL)
	{
		AXYZGameMode* GameMode = Cast<AXYZGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->PreLogout(this);
		}
	}

	Super::OnNetCleanup(Connection);
}

void AXYZPlayerController::UpdateMatchStatus_Implementation(int32 Status)
{
	MatchStatus = Status;
}

void AXYZPlayerController::SetVisibleEnemyActors_Implementation(const TArray<int32>& DeltaVisibleActors, const TArray<int32>& DeltaNonVisibleActors)
{
	NonVisibleEnemyActors = DeltaNonVisibleActors;
	VisibleEnemyActors = DeltaVisibleActors;

	TSet<AXYZActor*> VisibleActors;
	TSet<AXYZActor*> NonVisibleActors;

	TMap<int32, AXYZActor*> ActorsByUID = XYZGameState->ActorsByUID;

	for(int32 UActorId : DeltaVisibleActors)
	{
		if(ActorsByUID.Contains(UActorId))
		{
				VisibleActors.Add(ActorsByUID[UActorId]);
		}
	}

	for(int32 UActorId : DeltaNonVisibleActors)
	{
		if(ActorsByUID.Contains(UActorId))
		{
			NonVisibleActors.Add(ActorsByUID[UActorId]);
		}
	}

	MinimapManager->UpdateVisibleActors(VisibleActors, NonVisibleActors, TeamId);
}

void AXYZPlayerController::SendVisibilityGridCoords_Implementation(const TArray<FIntVector2>& DeltaVisible, const TArray<FIntVector2>& DeltaNonVisible)
{
	if(FogOfWar)
	{
		FogOfWar->Update(DeltaVisible, DeltaNonVisible);
	}
	
}

void AXYZPlayerController::UpdateClientVisibility_Implementation(
	const TArray<int32>& DeltaVisibleActors,
	const TArray<int32>& DeltaNonVisibleActors,
	const TArray<FIntVector2>& DeltaVisible,
	const TArray<FIntVector2>& DeltaNonVisible)
{
	if(FogOfWar)
	{
		FogOfWar->Update(DeltaVisible, DeltaNonVisible);
	}

	NonVisibleEnemyActors = DeltaNonVisibleActors;
	VisibleEnemyActors = DeltaVisibleActors;

	TSet<AXYZActor*> VisibleActors;
	TSet<AXYZActor*> NonVisibleActors;

	TMap<int32, AXYZActor*> ActorsByUID = XYZGameState->ActorsByUID;

	for(int32 UActorId : DeltaVisibleActors)
	{
		if(ActorsByUID.Contains(UActorId))
		{
			VisibleActors.Add(ActorsByUID[UActorId]);
		}
	}

	for(int32 UActorId : DeltaNonVisibleActors)
	{
		if(ActorsByUID.Contains(UActorId))
		{
			NonVisibleActors.Add(ActorsByUID[UActorId]);
		}
	}

	MinimapManager->UpdateVisibleActors(VisibleActors, NonVisibleActors, TeamId);
}

void AXYZPlayerController::UpdateVisibleActors()
{
	if(GetLocalRole() != ROLE_Authority)
	{
		if(GetWorld())
		{
			if(XYZGameState)
			{
				TArray<int32> ActorsNotFound;
				
				for(int32 VisibleActor : VisibleEnemyActors)
				{
					if(XYZGameState->ActorsByUID.Contains(VisibleActor) && XYZGameState->ActorsByUID[VisibleActor])
					{
						AXYZActor* Actor = XYZGameState->ActorsByUID[VisibleActor];
						Actor->SetActorHiddenInGame(false);
						Actor->bIsVisible = true;
					}else
					{
						ActorsNotFound.Add(VisibleActor);
					}
				}
				VisibleEnemyActors = ActorsNotFound;
				ActorsNotFound.Empty();
				for(int32 NonVisibleActor : NonVisibleEnemyActors)
				{
					if(XYZGameState->ActorsByUID.Contains(NonVisibleActor) && XYZGameState->ActorsByUID[NonVisibleActor])
					{
						XYZGameState->ActorsByUID[NonVisibleActor]->SetActorHiddenInGame(true);
						XYZGameState->ActorsByUID[NonVisibleActor]->bIsVisible = false;
					}
					else
					{
						ActorsNotFound.Add(NonVisibleActor);
					}
				}
				NonVisibleEnemyActors = ActorsNotFound;
			}
		}
	}
}

void AXYZPlayerController::UpdateMouseCursor()
{
	AXYZActor* HitActor = Cast<AXYZActor>(XYZActorHit.GetActor());
	if(HitActor && !HitActor->bIsVisible)
	{
		HitActor = nullptr;
	}
	bool bHoveringEnemy = HitActor && HitActor->TeamId != TeamId;

	if (bAttackModifier && SelectionStructure && !SelectionStructure->IsEmpty()) {

		if (HitActor) {
			if (bHoveringEnemy && !HitActor->IsA(AXYZResourceActor::StaticClass())) {
				CurrentMouseCursor = EMouseCursor::Crosshairs;
			}
			else {
				CurrentMouseCursor = EMouseCursor::ResizeUpDown;
			}
		}
		else {
			CurrentMouseCursor = EMouseCursor::ResizeLeftRight;
		}
	}
	else {
		if (SelectionStructure && SelectionStructure->IsEmpty()) {
			if (HitActor && bHoveringEnemy) {
				CurrentMouseCursor = EMouseCursor::TextEditBeam;
			}
			else {
				CurrentMouseCursor = EMouseCursor::Default;
			}
		}
		else {
			if (HitActor) {
				if (bHoveringEnemy) {
					if (HitActor->IsA(AXYZResourceActor::StaticClass())) {
						CurrentMouseCursor = EMouseCursor::GrabHandClosed;
					}
					else {
						CurrentMouseCursor = EMouseCursor::GrabHand;
					}
				}
				else {
					CurrentMouseCursor = EMouseCursor::Hand;
				}
			}
			else {
				CurrentMouseCursor = EMouseCursor::Default;
			}
		}
	}
}

void AXYZPlayerController::UpdateLoadingScreen_Implementation(const TArray<FString>& PlayerNames, const TArray<int32>& Ratings,
	const float LoadingPercentage)
{
	if(Ratings[0] > -10000 && Ratings[1] > -10000)
	{
		OnLoadingScreenEvent.Broadcast(PlayerNames,Ratings, LoadingPercentage);
	}
}

void AXYZPlayerController::ClearBuildingPlacement()
{
	if(PlacementBuilding)
	{
		PlacementBuilding->Destroy();
	}
	bIsPlacingBuilding = false;
	WorkerAbilityIndex = -1;
	WorkerActorId = -1;
}

FVector AXYZPlayerController::GetMouseToWorldPosition(APlayerController* PlayerController)
{
	if(!PlayerController)
		return FVector::ZeroVector;

	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

	FHitResult HitResult;
	const FVector Start = WorldLocation;
	const FVector End = Start + WorldDirection * 10000; 

	FCollisionQueryParams TraceParams(FName(TEXT("MouseToWorldTrace")), true, PlayerController->GetPawn());
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TraceParams.AddIgnoredActor(*ActorItr);
	}
	if(GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, TraceParams))
	{
		return HitResult.Location;
	}

	return FVector::ZeroVector;
}

void AXYZPlayerController::PlaySound_Implementation(ESoundTypes SoundType)
{
	if(XYZGameState && XYZGameState->SoundManager){
		XYZGameState->SoundManager->PlayNotification(SoundType);
	}
}

void AXYZPlayerController::MoveFromMinimap(FVector2D TargetLocation)
{
	if(!SelectionStructure->IsEmpty())
	{
		FVector WorldCoord(TargetLocation.X, TargetLocation.Y, -1000);

		FVector Start = WorldCoord;
		Start.Z = 1000.0f;
		FVector End = WorldCoord;

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams);

		if (bHit) {
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), -1, HitResult.Location, EXYZInputType::SECONDARY_INPUT, bPrimaryModifier);
		}
	}
}

void AXYZPlayerController::CancelProductionAtIndex_Implementation(int32 Index, int32 UActorId)
{
	if (GetLocalRole() != ROLE_Authority) return;
	
	AXYZGameMode* GameMode = GetWorld()->GetAuthGameMode<AXYZGameMode>();
	if (GameMode) {
		TMap<int32, AXYZActor*> ActorsByUId = XYZGameState->ActorsByUID;
		if(ActorsByUId.Contains(UActorId) && ActorsByUId[UActorId]->TeamId == TeamId)
		{
			AXYZBuilding* Building = Cast<AXYZBuilding>(ActorsByUId[UActorId]);
			if(Building)
			{
				Building->CancelProductionIndex = Index;
			}
		}
	}
}

void AXYZPlayerController::PlayAbilitySound_Implementation(int32 ActorUID, int32 AbilityIndex)
{
	if(XYZGameState)
	{
		if(XYZGameState->ActorsByUID.Contains(ActorUID))
		{
			AXYZActor* Actor = XYZGameState->ActorsByUID[ActorUID];
			if(Actor && Actor->bIsVisible && Actor->Abilities.IsValidIndex(AbilityIndex) && Actor->Abilities[AbilityIndex]->AbilitySoundEffect)
			{
				Actor->PlaySound(Actor->Abilities[AbilityIndex]->AbilitySoundEffect);
			}
		}
	}
}

void AXYZPlayerController::AttackMoveFromMinimap(FVector2D TargetLocation)
{
	if(!SelectionStructure->IsEmpty())
	{
		FVector WorldCoord(TargetLocation.X, TargetLocation.Y, -1000);

		FVector Start = WorldCoord;
		Start.Z = 1000.0f;
		FVector End = WorldCoord;

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams);

		if (bHit) {
			CreateAndQueueInput(SelectionStructure->ToActorIdArray(), -1, HitResult.Location, EXYZInputType::ATTACK_MOVE, bPrimaryModifier);
		}
		bAttackModifier = false;
	}
}

bool AXYZPlayerController::CanPlaceBuilding(FVector CenterLocation, int32 GridSizeX, int32 GridSizeY)
{
	if(CenterLocation.X < 0.0f || CenterLocation.X > 10000.0f) return false;
	if(CenterLocation.Y < 0.0f || CenterLocation.Y > 10000.0f) return false;

	float GridSize = 100.0f;
	float RayLength = 5000.0f;
	float MaxAcceptableHeightDifference = 1.0f;

	TArray<FVector> RayStartPoints;

	float HalfGridX = (GridSizeX % 2 == 0) ? (GridSizeX / 2) : (GridSizeX - 1) / 2;
	float HalfGridY = (GridSizeY % 2 == 0) ? (GridSizeY / 2) : (GridSizeY - 1) / 2;

	FVector BottomLeftWorld = CenterLocation - FVector(HalfGridX * GridSize, HalfGridY * GridSize, 0);

	for(int32 i = 0; i < GridSizeX; i++)
	{
		for(int32 j = 0; j < GridSizeY; j++)
		{
			FVector StartPoint = BottomLeftWorld + FVector(i * GridSize, j * GridSize, 0);
			RayStartPoints.Add(StartPoint);
		}
	}

	TArray<float> HitHeights;
	bool bCanPlace = true;
	for(FVector StartPoint : RayStartPoints)
	{
		FHitResult HitResult;
		FVector Start = StartPoint + FVector(0, 0, 50);
		FVector End = StartPoint - FVector(0, 0, RayLength);
		FCollisionQueryParams CollisionParams;
		CollisionParams.bTraceComplex = true;
		for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if(!(*ActorItr)->IsA(AXYZResourceActor::StaticClass()))
			{
				CollisionParams.AddIgnoredActor(*ActorItr);
			}
		}
		
		if(GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams))
		{
			if(HitResult.GetActor()->IsA(AXYZResourceActor::StaticClass()))
			{
				return false;
			}
			HitHeights.Add(HitResult.ImpactPoint.Z);
		}
	}

	if(HitHeights.Num() == 0 || !bCanPlace)
		return false;

	float MaxZ = FMath::Max(HitHeights);
	float MinZ = FMath::Min(HitHeights);
	if(MaxZ - MinZ > MaxAcceptableHeightDifference)
		return false;

	TArray<AXYZBuilding*> Buildings;
	TArray<FVector2D> GridPoints;

	for(FVector RayPoints : RayStartPoints)
	{
		GridPoints.Add(FVector2D(FMath::FloorToInt(RayPoints.X / 100.0f), FMath::FloorToInt(RayPoints.Y / 100.0f)));
	}
	for (TActorIterator<AXYZBuilding> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(*ActorItr != PlacementBuilding)
		{
			Buildings.Add(*ActorItr);
		}
	}


	for(FVector2D Point : GridPoints)
	{
		for(AXYZBuilding* Building : Buildings)
		{
			if(IsPointInBuildingGridArea(Point, Building))
			{
				return false;
			}
		}
	}
	return true;
}

bool AXYZPlayerController::IsPointInBuildingGridArea(const FVector2D& Point, AXYZBuilding* Building)
{
	FIntVector2 BuildingGridPosition = FIntVector2(FMath::FloorToInt(Building->GetActorLocation().X / 100.0f), FMath::FloorToInt(Building->GetActorLocation().Y / 100.0f));
	FIntVector2 BuildingGridSize = FIntVector2(Building->GridSize.X, Building->GridSize.Y);

	float HalfGridX = (BuildingGridSize.X % 2 == 0) ? (BuildingGridSize.X / 2) : (BuildingGridSize.X - 1) / 2;
	float HalfGridY = (BuildingGridSize.Y % 2 == 0) ? (BuildingGridSize.Y / 2) : (BuildingGridSize.Y - 1) / 2;

	FIntVector2 BottomLeft = BuildingGridPosition - FIntVector2(HalfGridX, HalfGridY);
    
	FIntVector2 TopRight = BuildingGridPosition + FIntVector2(HalfGridX, HalfGridY);

	return Point.X >= BottomLeft.X && Point.X <= TopRight.X &&
		   Point.Y >= BottomLeft.Y && Point.Y <= TopRight.Y;
}