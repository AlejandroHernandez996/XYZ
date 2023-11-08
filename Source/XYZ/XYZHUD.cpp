// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZHUD.h"
#include "XYZPlayerController.h"

void AXYZHUD::BeginPlay() {
    Super::BeginPlay();
}

void AXYZHUD::DrawHUD()
{
    Super::DrawHUD();
    if (bSelectActors) {
        if(XYZPlayerController)
        {
            int32 ViewportSizeX, ViewportSizeY;
            XYZPlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
            GetActorsInSelectionRectangle(TopLeft, FVector2D(ViewportSizeX, ViewportSizeY), AllActorsOnScreen, false);  
        }
        GetActorsInSelectionRectangle(BoxStart, BoxEnd, SelectedActors, false);
    }
    else {
        ClearActors();
    }
}