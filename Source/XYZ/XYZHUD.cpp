// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZHUD.h"
#include "XYZActor.h"

void AXYZHUD::BeginPlay() {
    Super::BeginPlay();
    BottomRight = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
}

void AXYZHUD::DrawHUD()
{
    Super::DrawHUD();
    if (bSelectActors) {
        GetActorsInSelectionRectangle(TopLeft, BottomRight, AllActorsOnScreen, false);
        GetActorsInSelectionRectangle(BoxStart, BoxEnd, SelectedActors, false);
    }
    else {
        ClearActors();
    }
}