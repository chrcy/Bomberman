// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpBase.h"
#include "PowerUpSpeed.generated.h"

UCLASS(blueprintable)
class BOMBERMAN1_API APowerUpSpeed : public APowerUpBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpSpeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Overlap
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult &SweepResult) override;
};
