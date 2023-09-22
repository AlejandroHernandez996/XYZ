#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZAbility.generated.h"

/**
 * Represents a basic ability in the XYZ game.
 */
UCLASS(Abstract)
class XYZ_API UXYZAbility : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        FString Name;

    UFUNCTION()
        virtual void Activate() {};
};