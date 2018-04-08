// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpBase.h"
#include "Components/BoxComponent.h"
#include "Components/MaterialBillboardComponent.h"

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetBoxExtent(FVector(50, 50, 50));

	// setup collision to overlap, but block line trace (enables bombs to destroy item)
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	// holds icon for power up
	MaterialBillboardComponent = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("MaterialBillboard"));
	MaterialBillboardComponent->SetupAttachment(BoxComponent);

	// Setup overlap begin delegate
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUpBase::BeginOverlap);
}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set icon to display for powerup
void APowerUpBase::SetIcon(class UMaterialInterface* Material)
{
	// set icon
	FMaterialSpriteElement item;
	item.Material = Material;
	item.BaseSizeX = 45;
	item.BaseSizeY = 45;
	MaterialBillboardComponent->Elements.Add(item);
}

void APowerUpBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

}

void APowerUpBase::Destroyed_Implementation()
{
	Destroy();
}
