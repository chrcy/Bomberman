// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyInterface.h"
#include "PowerUpBase.generated.h"

UCLASS(abstract, blueprintable)
class BOMBERMAN1_API APowerUpBase : public AActor, public IDestroyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when a bomb has destroyed you
	void Destroyed_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	class UMaterialBillboardComponent* MaterialBillboardComponent;

	// Set icon to display for powerup
	void SetIcon(class UMaterialInterface* Material);

	// Called when overlap begins with another component
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
		
	// how long to stay alive after spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float AliveTime = 5;

	// will appear after this time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float VisibleDelay = 2;

	// Play sound when collected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	class USoundWave* CollectSound;
};
