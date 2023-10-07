#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XYZAbility.generated.h"

/**
 * Represents a basic ability in the XYZ game.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class XYZ_API UXYZAbility : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
        FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
    UTexture2D* AbilityImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MineralCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 SupplyCost;

    
    UFUNCTION()
        virtual void Activate() {};
};