// Fill out your copyright notice in the Description page of Project Settings.

#include "XYZCameraController.h"
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
	FVector2D MousePosition = GetMousePositionOnViewport();
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector2D NormalizedMousePosition = MousePosition / ViewportSize;
	FVector RIGHT = FVector(1.0f, 0.0f, 0.0f);
	FVector LEFT = FVector(-1.0f, 0.0f, 0.0f);
	FVector UP = FVector(0.0f, 1.0f, 0.0f);
	FVector DOWN = FVector(0.0f, -1.0f, 0.0f);

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
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

void AXYZCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AXYZCameraController::MoveCamera(const FVector& Direction)
{
	FVector WorldDirection = CameraBoom->GetComponentRotation().RotateVector(Direction);
	WorldDirection.Z = 0;
	FVector NewCameraLocation = GetActorLocation() + WorldDirection * EdgePanSpeed * GetWorld()->DeltaTimeSeconds;

	SetActorLocation(NewCameraLocation);
}