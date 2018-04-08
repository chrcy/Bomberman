// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpExplosion.h"
#include "Components/MaterialBillboardComponent.h"
#include "ConstructorHelpers.h"
#include "Materials/Material.h"
#include "PowerUpInterface.h"
#include "PlayerCharacter.h"

// Sets default values
APowerUpExplosion::APowerUpExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetIcon(ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/M_PowerupExplosion.M_PowerupExplosion'")).Object);
}

// Called when the game starts or when spawned
void APowerUpExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUpExplosion::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// increase skill
	if (OtherActor->GetClass()->ImplementsInterface(UPowerUpInterface::StaticClass()))
	{
		IPowerUpInterface::Execute_IncreaseExplosion(OtherActor);

		// remove actor, as it has been collected
		Destroy();
	}
}