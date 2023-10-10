// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "XYZCameraController.generated.h"

UCLASS()
class XYZ_API AXYZCameraController : public APawn
{
	GENERATED_BODY()

public:
	AXYZCameraController();

protected:
	virtual void BeginPlay() override;

	FVector2D GetMousePositionOnViewport() const;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void StartDragMovement();
	void DragMove();
	void EndDragMovement();
	bool bBlockMovementFlag = false;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY()
	class AXYZPlayerController* XYZPlayerController;

private:
	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float EdgePanSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float EdgePanThreshold;

	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		FRotator CameraBoomRotation;

	FVector LastDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	void MoveCamera(const FVector& Direction, float Speed);

	FTimerHandle DragMoveTimerHandle;
	FVector2D InitialDragMousePosition;
	FVector InitialDragCameraPosition;
	bool bIsDragging = false;
	const float DragSpeed = 3000.0f;
};
