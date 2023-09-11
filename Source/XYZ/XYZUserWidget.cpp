#include "XYZUserWidget.h"

void UXYZUserWidget::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    Super::NativeOnMouseEnter(MyGeometry, MouseEvent);

    // Mouse entered, so set bIsMouseHovered to true
    bIsMouseHovered = true;

    // Broadcast the delegate event
    OnMouseHovered.Broadcast();
}

void UXYZUserWidget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
    Super::NativeOnMouseLeave(MouseEvent);

    // Mouse left, so set bIsMouseHovered to false
    bIsMouseHovered = false;

    // Broadcast the delegate event
    OnMouseHovered.Broadcast();
}