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
    int32 GasCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 SupplyCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 EnergyCost;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Requirements")
    TMap<int32, FString> ActorRequirements;

    UPROPERTY()
    class AXYZActor* OwningActor;
    
    UFUNCTION()
        virtual bool Activate();

    UFUNCTION(BlueprintCallable)
    FString GetRequirementsToString()
    {
        FString RequirementsString = "";
    
        for (const auto& Elem : ActorRequirements)
        {
            RequirementsString += FString::Printf(TEXT("%s\n"), *Elem.Value);
        }
    
        return RequirementsString;
    }

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    class USoundBase* AbilitySoundEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UDecalComponent* AbilityGroundDecal;

    UPROPERTY()
    FVector TargetLocation;
};