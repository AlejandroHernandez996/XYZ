#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XYZUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseHoveredEvent);
/**
 *
 */
UCLASS()
class XYZ_API UXYZUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;

    UPROPERTY(BlueprintReadOnly, Category = "Mouse")
        bool bIsMouseHovered;

    UPROPERTY(BlueprintAssignable, Category = "Mouse")
        FOnMouseHoveredEvent OnMouseHovered;
};