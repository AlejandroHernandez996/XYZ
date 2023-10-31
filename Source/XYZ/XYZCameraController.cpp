// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZCameraController.h"

#include "EngineUtils.h"
#include "XYZPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AXYZCameraController::AXYZCameraController()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); 
	CameraBoom->TargetArmLength = 4000.0f; 
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 45.0f, 0.0f));  
	CameraBoom->bDoCollisionTest = false; 

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; 
	TopDownCameraComponent->FieldOfView = 30.0f; 

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	EdgePanThreshold = .1f; 
	EdgePanSpeed = 1000.0f;  
}
void AXYZCameraController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() != ROLE_Authority)
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	}
}

void AXYZCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float x, y;
	if (GetLocalRole() == ROLE_Authority || !GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y) || bBlockMovementFlag) {
		return;
	}
	if(bIsDragging)
	{
		DragMove();
		return;
	}
	FVector2D MousePosition = GetMousePositionOnViewport();
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector2D NormalizedMousePosition = MousePosition / ViewportSize;
	FVector RIGHT = FVector(1.0f, 0.0f, 0.0f);
	FVector LEFT = FVector(-1.0f, 0.0f, 0.0f);
	FVector UP = FVector(0.0f, 1.0f, 0.0f);
	FVector DOWN = FVector(0.0f, -1.0f, 0.0f);

	if (NormalizedMousePosition.X <= EdgePanThreshold)
	{
		MoveCamera(DOWN, EdgePanSpeed);
	}
	else if (NormalizedMousePosition.X >= 1.0f - EdgePanThreshold)
	{
		MoveCamera(UP, EdgePanSpeed);
	}

	if (NormalizedMousePosition.Y <= EdgePanThreshold)
	{
		MoveCamera(RIGHT, EdgePanSpeed);
	}
	else if (NormalizedMousePosition.Y >= 1.0f - EdgePanThreshold)
	{
		MoveCamera(LEFT, EdgePanSpeed);
	}

	
}

FVector2D AXYZCameraController::GetMousePositionOnViewport() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

void AXYZCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AXYZCameraController::StartDragMovement()
{
	if(XYZPlayerController)
	{
		FVector2D CurrentMousePosition;
		XYZPlayerController->GetMousePosition(CurrentMousePosition.Y, CurrentMousePosition.X);
		InitialDragMousePosition = CurrentMousePosition;
		bIsDragging = true;
	}
}

void AXYZCameraController::DragMove()
{
	if (!bIsDragging)
		return;

	if (XYZPlayerController)
	{
		FVector2D CurrentMousePosition;
		XYZPlayerController->GetMousePosition(CurrentMousePosition.Y, CurrentMousePosition.X);
		FVector2D MouseDelta = CurrentMousePosition - InitialDragMousePosition;

		FVector CameraDelta(MouseDelta.X, -MouseDelta.Y, 0);
		CameraDelta.Normalize();
		MoveCamera(CameraDelta, DragSpeed);

		InitialDragMousePosition = CurrentMousePosition;
	}
}

void AXYZCameraController::EndDragMovement()
{
	bIsDragging = false;
}

TArray<FVector2D> AXYZCameraController::GetCameraCorners()
{
	TArray<FVector> CameraCorners;
	TArray<FVector> CameraCornersDirections;
	TArray<FVector2D> CameraCornersWorld;

	int32 ViewportSizeX, ViewportSizeY;
	XYZPlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D TopLeftScreen(0.0f, 0.0f);
	FVector2D TopRightScreen(ViewportSizeX, 0.0f);
	FVector2D BottomLeftScreen(0.0f, ViewportSizeY);
	FVector2D BottomRightScreen(ViewportSizeX, ViewportSizeY);

	FVector TopLeftWorld, TopRightWorld, BottomLeftWorld, BottomRightWorld;
	FVector TopLeftWorldDir, TopRightWorldDir, BottomLeftWorldDir, BottomRightWorldDir;
	XYZPlayerController->DeprojectScreenPositionToWorld(TopLeftScreen.X,TopLeftScreen.Y, TopLeftWorld, TopLeftWorldDir);
	XYZPlayerController->DeprojectScreenPositionToWorld(TopRightScreen.X,TopRightScreen.Y, TopRightWorld, TopRightWorldDir);
	XYZPlayerController->DeprojectScreenPositionToWorld(BottomLeftScreen.X,BottomLeftScreen.Y, BottomLeftWorld, BottomLeftWorldDir);
	XYZPlayerController->DeprojectScreenPositionToWorld(BottomRightScreen.X, BottomRightScreen.Y, BottomRightWorld, BottomRightWorldDir);
	CameraCorners.Add(TopLeftWorld);
	CameraCorners.Add(TopRightWorld);
	CameraCorners.Add(BottomLeftWorld);
	CameraCorners.Add(BottomRightWorld);
	CameraCornersDirections.Add(TopLeftWorldDir);
	CameraCornersDirections.Add(TopRightWorldDir);
	CameraCornersDirections.Add(BottomLeftWorldDir);
	CameraCornersDirections.Add(BottomRightWorldDir);

	for(int32 i = 0;i < 4;i++)
	{
		FHitResult HitResult;
		const FVector Start = CameraCorners[i];
		const FVector End = Start + CameraCornersDirections[i] * 10000; 
		FCollisionQueryParams TraceParams(FName(TEXT("MouseToWorldTrace")), true, XYZPlayerController->GetPawn());
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;
		for (TActorIterator<AXYZActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			TraceParams.AddIgnoredActor(*ActorItr);
		}
		if(GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, TraceParams))
		{
			FVector HitLocation = HitResult.Location;
			HitLocation.Z = 1000.0f;
			FVector EndLocation = HitLocation;
			EndLocation.Z = 0.0f;
			CameraCornersWorld.Add(FVector2D(HitLocation.X,HitLocation.Y));
		}
	}
	return CameraCornersWorld;
}

void AXYZCameraController::SaveCameraLocation(int32 CameraGroupIndex)
{
	CameraLocations.Add(CameraGroupIndex, FVector2D(GetActorLocation().X, GetActorLocation().Y));
}

void AXYZCameraController::JumpToCameraLocation(int32 CameraGroupIndex)
{
	if(CameraLocations.Contains(CameraGroupIndex))
	{
		SetActorLocation(FVector(CameraLocations[CameraGroupIndex].X, CameraLocations[CameraGroupIndex].Y, GetActorLocation().Z));
	}
}

void AXYZCameraController::MoveCamera(const FVector& Direction, float Speed)
{
	FVector WorldDirection = CameraBoom->GetComponentRotation().RotateVector(Direction);
	WorldDirection.Z = 0;
	FVector NewCameraLocation = GetActorLocation() + WorldDirection * Speed * GetWorld()->DeltaTimeSeconds;

	float MinX = -1000.0f;
	float MaxX = 11000.0f;
	float MinY = -1000.0f;
	float MaxY = 11000.0f;

	FVector ClampedLocation;
	ClampedLocation.X = FMath::Clamp(NewCameraLocation.X, MinX, MaxX);
	ClampedLocation.Y = FMath::Clamp(NewCameraLocation.Y, MinY, MaxY);
	ClampedLocation.Z = NewCameraLocation.Z; 

	SetActorLocation(ClampedLocation);
}
