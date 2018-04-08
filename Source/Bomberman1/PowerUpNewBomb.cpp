// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpNewBomb.h"
#include "ConstructorHelpers.h"
#include "Materials/Material.h"
#include "PowerUpInterface.h"
#include "PlayerCharacter.h"

// Sets default values
APowerUpNewBomb::APowerUpNewBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetIcon(ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/M_PowerupBomb.M_PowerupBomb'")).Object);
}

// Called when the game starts or when spawned
void APowerUpNewBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpNewBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUpNewBomb::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// increase skill
	if (OtherActor->GetClass()->ImplementsInterface(UPowerUpInterface::StaticClass()))
	{
		IPowerUpInterface::Execute_IncreaseBombs(OtherActor);

		// remove actor, as it has been collected
		Destroy();
	}
}