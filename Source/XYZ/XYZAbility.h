#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZAbility.generated.h"

/**
 * Represents a basic ability in the XYZ game.
 */
UCLASS()
class XYZ_API UXYZAbility : public UObject
{
    GENERATED_BODY()

public:
    /** The unique ID of the ability. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        int32 ID;

    /** The name of the ability. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        FString Name;

    /** The cooldown duration of the ability in seconds. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        float Cooldown;

};