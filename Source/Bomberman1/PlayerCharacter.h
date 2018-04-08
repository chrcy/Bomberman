// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DestroyInterface.h"
#include "PowerUpInterface.h"
#include "BombInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS(blueprintable)
class BOMBERMAN1_API APlayerCharacter : public ACharacter, public IDestroyInterface, public IPowerUpInterface, public IBombInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when a bomb has destroyed you
	void Destroyed_Implementation() override;

	// makes you go faster
	void IncreaseSpeed_Implementation() override;

	// can drop more bombs at once
	void IncreaseBombs_Implementation() override;

	// bombs explode further
	void IncreaseExplosion_Implementation() override;

	// Called to drob a bomb
	void DropBomb_Implementation() override;

	// Called when the bomb has exploded
	void BombExploded_Implementation() override;

	//Input functions
	void Player1MoveUp(float AxisValue);
	void Player1MoveRight(float AxisValue);
	void Player1DropBomb();

	void Player2MoveUp(float AxisValue);
	void Player2MoveRight(float AxisValue);
	void Player2DropBomb();

protected:

	// how many bombs can be dropped at the same time
	UPROPERTY(transient)
	int32 MaxBombs = 1;

	// how many bombs are currently active
	UPROPERTY(transient)
	int32 NumBombs = 0;

	// how far damage will occur (in all directions)
	UPROPERTY(transient)
	float ExplosionLength = 100;
};
