// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZCameraController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h" // Include this header
#include "Engine/World.h"

AXYZCameraController::AXYZCameraController()
{
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->SetRelativeRotation(CameraBoomRotation);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	EdgePanThreshold = .1f; // Adjust as needed
	EdgePanSpeed = 1000.0f;   // Adjust as needed
}
void AXYZCameraController::BeginPlay()
{
	Super::BeginPlay();
}

void AXYZCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetLocalRole() == ROLE_Authority) {
		return;
	}
	FVector2D MousePosition = GetMousePositionOnViewport();
	if (MousePosition.X == 0.0f && MousePosition.Y == 0.0f)
	{
		return;
	}

	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	// Calculate normalized mouse position
	FVector2D NormalizedMousePosition = MousePosition / ViewportSize;
	
	// Log the mouse position and normalized position
	//UE_LOG(LogTemp, Warning, TEXT("Mouse Position: %s, Normalized: %s"), *MousePosition.ToString(), *NormalizedMousePosition.ToString());

	FVector RIGHT = FVector(1.0f, 0.0f, 0.0f);
	FVector LEFT = FVector(-1.0f, 0.0f, 0.0f);
	FVector UP = FVector(0.0f, 1.0f, 0.0f);
	FVector DOWN = FVector(0.0f, -1.0f, 0.0f);

	// Move camera when mouse is near the edges
	if (NormalizedMousePosition.X <= EdgePanThreshold)
	{
		MoveCamera(DOWN);
	}
	else if (NormalizedMousePosition.X >= 1.0f - EdgePanThreshold)
	{
		MoveCamera(UP);
	}

	if (NormalizedMousePosition.Y <= EdgePanThreshold)
	{
		MoveCamera(RIGHT);
	}
	else if (NormalizedMousePosition.Y >= 1.0f - EdgePanThreshold)
	{
		MoveCamera(LEFT);
	}

}

FVector2D AXYZCameraController::GetMousePositionOnViewport() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0); // Change 0 to the appropriate player index
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

// Called to bind functionality to input
void AXYZCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AXYZCameraController::MoveCamera(const FVector& Direction)
{
	// Calculate the camera's new location based on the direction
	FVector NewCameraLocation = TopDownCameraComponent->GetComponentLocation() + Direction * EdgePanSpeed * GetWorld()->DeltaTimeSeconds;

	// Limit the camera's movement within reasonable bounds
	// You can customize this based on your level's bounds
	FVector MinCameraLocation = FVector(-100000.0f, -100000.0f, 0.0f);
	FVector MaxCameraLocation = FVector(100000.0f, 100000.0f, 0.0f);
	NewCameraLocation.X = FMath::Clamp(NewCameraLocation.X, MinCameraLocation.X, MaxCameraLocation.X);
	NewCameraLocation.Y = FMath::Clamp(NewCameraLocation.Y, MinCameraLocation.Y, MaxCameraLocation.Y);

	// Set the new camera location
	TopDownCameraComponent->SetWorldLocation(NewCameraLocation);
}