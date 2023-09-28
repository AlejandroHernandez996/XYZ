#include "XYZUserWidget.h"

void UXYZUserWidget::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    Super::NativeOnMouseEnter(MyGeometry, MouseEvent);

    bIsMouseHovered = true;
    OnMouseHovered.Broadcast();
}

void UXYZUserWidget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
    Super::NativeOnMouseLeave(MouseEvent);

    bIsMouseHovered = false;
    OnMouseHovered.Broadcast();
}