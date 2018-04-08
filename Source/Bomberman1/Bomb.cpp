// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ExplosionLine.h"
#include "Engine/World.h"
#include "BombInterface.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);

	// setup collision to overlap, but block line trace (enables bombs to destroy item)
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);

	BoxComponent->SetBoxExtent(FVector(40, 40, 40));

	// Setup overlap begin delegate
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABomb::EndOverlap);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	StaticMeshComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Mesh/Bomb.Bomb'")).Object);
	StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// need to disable collision initially, otherwise player interfers with the bomb they just placed
	// collision is turned on after player leaves bomb area
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set sounds
	BombChargeSound = ConstructorHelpers::FObjectFinder<USoundWave>(TEXT("SoundWave'/Game/Audio/BombCharge.BombCharge'")).Object;
	BombExplosionSound = ConstructorHelpers::FObjectFinder<USoundWave>(TEXT("SoundWave'/Game/Audio/Explosion.Explosion'")).Object;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	// make dynamic so we can change colour
	DynamicMaterial = StaticMeshComponent->CreateDynamicMaterialInstance(0);

	// ticking sound
	UGameplayStatics::PlaySoundAtLocation(this, BombChargeSound, GetActorLocation());
}

void ABomb::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	// explosion sound
	UGameplayStatics::PlaySoundAtLocation(this, BombExplosionSound, GetActorLocation());

	// notify player that their bomb has exploded (i.e. they can drop another one now)
	AActor* Actor = GetOwner();
	if (Actor->GetClass()->ImplementsInterface(UBombInterface::StaticClass()))
		IBombInterface::Execute_BombExploded(Actor);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float timeSinceCreation = GetGameTimeSinceCreation();

	// update bomb material norm time
	if (DynamicMaterial)
	{
		float normTime = timeSinceCreation / FuzeTime;
		DynamicMaterial->SetScalarParameterValue(TEXT("NormTimeAlive"), normTime);
	}

	// destroy bomb if fuze time exceeded
	if (timeSinceCreation >= FuzeTime)
	{
		Destroy();

		// spawn explosion lines in all directions
		FVector Location = GetActorLocation();
		FActorSpawnParameters SpawnInfo;
		AExplosionLine *ExplosionLine1 = GetWorld()->SpawnActor<AExplosionLine>(Location, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
		ExplosionLine1->MaxLength = ExplosionLength;
		AExplosionLine *ExplosionLine2 = GetWorld()->SpawnActor<AExplosionLine>(Location, FRotator(0.0f, 90.0f, 0.0f), SpawnInfo);
		ExplosionLine2->MaxLength = ExplosionLength;
		AExplosionLine *ExplosionLine3 = GetWorld()->SpawnActor<AExplosionLine>(Location, FRotator(0.0f, 180.0f, 0.0f), SpawnInfo);
		ExplosionLine3->MaxLength = ExplosionLength;
		AExplosionLine *ExplosionLine4 = GetWorld()->SpawnActor<AExplosionLine>(Location, FRotator(0.0f, 270.0f, 0.0f), SpawnInfo);
		ExplosionLine4->MaxLength = ExplosionLength;
	}
}

void ABomb::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// now safe to turn on collision
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABomb::Destroyed_Implementation()
{
	Destroy();
}