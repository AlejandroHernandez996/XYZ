#pragma once

#include "Processable.generated.h"

UINTERFACE(Blueprintable)
class UProcessable : public UInterface
{
	GENERATED_BODY()
};

class IProcessable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Process(float DeltaTime) = 0;
};