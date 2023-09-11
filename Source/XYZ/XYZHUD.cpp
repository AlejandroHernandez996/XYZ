// Fill out your copyright notice in the Description page of Project Settings.


#include "XYZHUD.h"
#include "XYZActor.h"

void AXYZHUD::DrawHUD()
{
    Super::DrawHUD();

    if (bSelectActors) {
        GetActorsInSelectionRectangle(BoxStart, BoxEnd, SelectedActors, false);
    }
    else {
        ClearActors();
    }
}