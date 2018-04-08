// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BombInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UBombInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement this for characters that drop bombs
 */
class BOMBERMAN1_API IBombInterface
{
	GENERATED_BODY()

public:
	
	// Called to drob a bomb
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Bomb)
	void DropBomb();

	// Called when the bomb has exploded
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Bomb)
	void BombExploded();
};
