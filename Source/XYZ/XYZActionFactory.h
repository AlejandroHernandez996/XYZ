// XYZActionFactory.h

#pragma once

#include "CoreMinimal.h"
#include "XYZActionFactory.generated.h"

UCLASS()
class XYZ_API UXYZActionFactory : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Action")
       static UXYZAction* CreateAction(TArray<int32> SelectedActors, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount, AXYZGameState* GameState);

    UFUNCTION(BlueprintCallable, Category = "Action")
       static UXYZAction* MakeAction(TArray<int32> SelectedActors, AXYZActor* _TargetActor, FVector _TargetLocation, bool _bQueueInput, EXYZInputType InputType, int32 ActionCount, UClass* ActionClass, FName ActionName, AXYZGameState* GameState);
};