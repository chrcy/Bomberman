// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyInterface.h"
#include "Bomb.generated.h"

UCLASS(blueprintable)
class BOMBERMAN1_API ABomb : public AActor, public IDestroyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends or when destroyed
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Overlap
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when a bomb has destroyed you
	void Destroyed_Implementation() override;

	// Used for collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* BoxComponent;

	// mesh to draw for bomb
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* StaticMeshComponent;

	// sound to play before bomb explodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class USoundWave* BombChargeSound;

	// sound to play when bomb explodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class USoundWave* BombExplosionSound;

	// time before bomb explodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float FuzeTime = 3;

	// how far damage will occure (in all directions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float ExplosionLength = 100;

protected:

	UPROPERTY(transient)
	class UMaterialInstanceDynamic* DynamicMaterial;
};
