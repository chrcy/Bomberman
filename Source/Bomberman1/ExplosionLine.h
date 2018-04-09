// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionLine.generated.h"

UCLASS(blueprintable)
class BOMBERMAN1_API AExplosionLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// mesh to draw for explosion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* StaticMeshComponent;

	// How Far to cause damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float MaxLength = 100;

	// Current length of damage line
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float CurrentLength = 0;

	// Rate of increase for damage line
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float GrowRate = 1000;

	// Height offset to perform line trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float HeightOffset = 50;

	// How long explosion last for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float ExplosionDuration = 2;

	// Used for collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* BoxComponent;

protected:

	UPROPERTY(transient)
	FVector Location;

	UPROPERTY(transient)
	bool bCanGrow = true;
};
