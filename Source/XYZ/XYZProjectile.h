#pragma once

#include "CoreMinimal.h"
#include "Processable.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "XYZProjectile.generated.h"

UCLASS()
class XYZ_API AXYZProjectile : public AActor, public IProcessable
{
	GENERATED_BODY()

public:
	AXYZProjectile();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void MoveToTarget(float DeltaTime);
	UFUNCTION()
	void Process(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAliveTime = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeAlive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestroyDistance = 5.0f;
	UPROPERTY(Replicated)
	FVector TargetLocation;
	UPROPERTY()
	class AXYZActor* TargetActor;
	UPROPERTY()
	AXYZActor* OwningActor;
	UPROPERTY()
	bool bDestroyFlag;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
