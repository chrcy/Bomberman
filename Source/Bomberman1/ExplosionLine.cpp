// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosionLine.h"
#include "Engine/World.h"
#include "DestroyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
AExplosionLine::AExplosionLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
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

	// set points for line trace
	FVector StartPoint = GetActorLocation();
	FVector EndPoint = StartPoint + GetActorForwardVector() * CurrentLength;

	// perform line trace, to see what we damaged
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	bool Result = UKismetSystemLibrary::LineTraceSingle(this, StartPoint, EndPoint, 
		ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, 
		EDrawDebugTrace::ForOneFrame, HitResult, true);

	if (Result)
	{
		// destroy hit actor (if it implements interface)
		AActor* Actor = HitResult.Actor.Get();
		if (Actor->GetClass()->ImplementsInterface(UDestroyInterface::StaticClass()))
		{
			IDestroyInterface::Execute_Destroyed(Actor);
			Destroy();
		}

		bCanGrow = false;
	}

	// Destroy once explosion time has elapsed
	if (GetGameTimeSinceCreation() > ExplosionDuration)
	{
		Destroy();
	}
}

