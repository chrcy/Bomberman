// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerUpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UPowerUpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOMBERMAN1_API IPowerUpInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = PowerUp)
	void IncreaseSpeed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = PowerUp)
	void IncreaseBombs();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = PowerUp)
	void IncreaseExplosion();
};
