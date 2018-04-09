// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosionLine.h"
#include "Engine/World.h"
#include "DestroyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AExplosionLine::AExplosionLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetWorldScale3D(FVector(0.0f, 0.0f, 0.0f));
	StaticMeshComponent->SetRelativeLocation(FVector(0, 0, 50));
	StaticMeshComponent->SetRelativeRotation(FRotator(0, 180, 0));

	StaticMeshComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Mesh/Plane.Plane'")).Object);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	Location = GetActorLocation();
}

// Called when the game starts or when spawned
void AExplosionLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosionLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// increase line length
	if (bCanGrow)
	{
		CurrentLength += DeltaTime * GrowRate;
		CurrentLength = FMath::Clamp(CurrentLength, 0.0f, MaxLength);
	}

	float Length = 50 + CurrentLength;
	StaticMeshComponent->SetWorldScale3D(FVector(Length / 100.0, 2.25f, 1.0f));
	StaticMeshComponent->SetRelativeLocation(FVector(CurrentLength / 2, 0, 0));

	// set points for line trace
	FVector StartPoint = GetActorLocation();
	FVector EndPoint = StartPoint + GetActorForwardVector() * CurrentLength;

	// perform line trace, to see what we damaged
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	bool Result = UKismetSystemLibrary::LineTraceSingle(this, StartPoint, EndPoint, 
		ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, 
		EDrawDebugTrace::None, HitResult, true);

	if (Result)
	{
		// destroy hit actor (if it implements interface)
		AActor* Actor = HitResult.Actor.Get();
		if (Actor->GetClass()->ImplementsInterface(UDestroyInterface::StaticClass()))
		{
			IDestroyInterface::Execute_Destroyed(Actor);
			//Destroy();
		}

		bCanGrow = false;
	}

	// Destroy once explosion time has elapsed
	if (GetGameTimeSinceCreation() > ExplosionDuration)
	{
		Destroy();
	}
}

