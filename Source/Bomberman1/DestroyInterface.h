// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestroyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDestroyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement this for classes that can be destroyed by bomb, etc
 */
class BOMBERMAN1_API IDestroyInterface
{
	GENERATED_BODY()

public:
	
	// Called when you should be destroyed
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Destroy)
	void Destroyed();
};
