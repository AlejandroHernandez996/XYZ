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
	CameraBoom->TargetArmLength = 4000.0f;  // You can tweak this distance as per your need
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 45.0f, 0.0f));  // Set isometric angles
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	TopDownCameraComponent->FieldOfView = 30.0f;  // Flatten the view for an isometric look

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	EdgePanThreshold = .1f; // Adjust as needed
	EdgePanSpeed = 1000.0f;   // Adjust as needed
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
	if (GetLocalRole() == ROLE_Authority || !GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y)) {
		return;
	}
	FVector2D MousePosition = GetMousePositionOnViewport();
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector2D NormalizedMousePosition = MousePosition / ViewportSize;
	UE_LOG(LogTemp, Warning, TEXT("Mouse Position: %s, Normalized: %s"), *MousePosition.ToString(), *NormalizedMousePosition.ToString());
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
	FVector WorldDirection = CameraBoom->GetComponentRotation().RotateVector(Direction);

	// If you want to project the motion onto a plane (in this case, the XY plane),
	// you can nullify the Z-component of the movement vector.
	WorldDirection.Z = 0;

	// Calculate the camera's new location based on the direction
	FVector NewCameraLocation = GetActorLocation() + WorldDirection * EdgePanSpeed * GetWorld()->DeltaTimeSeconds;

	// Set the new camera location
	SetActorLocation(NewCameraLocation);
}