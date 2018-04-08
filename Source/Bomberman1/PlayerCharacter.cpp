// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Bomb.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent)
		MovementComponent->MaxWalkSpeed = 200;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// bind axis/actions that are setup in the editor
	
	PlayerInputComponent->BindAction("Player1DropBomb", IE_Pressed, this, &APlayerCharacter::Player1DropBomb);
	PlayerInputComponent->BindAction("Player2DropBomb", IE_Pressed, this, &APlayerCharacter::Player2DropBomb);

	PlayerInputComponent->BindAxis("Player1Up", this, &APlayerCharacter::Player1MoveUp);
	PlayerInputComponent->BindAxis("Player2Up", this, &APlayerCharacter::Player2MoveUp);
	PlayerInputComponent->BindAxis("Player1Right", this, &APlayerCharacter::Player1MoveRight);
	PlayerInputComponent->BindAxis("Player2Right", this, &APlayerCharacter::Player2MoveRight);
}

void APlayerCharacter::Destroyed_Implementation()
{
	// hide destroyed actor
	SetActorHiddenInGame(true);

	// Stop any more input
	APlayerController* PlayerController0 = UGameplayStatics::GetPlayerController(this, 0);
	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(this, 1);
	this->DisableInput(PlayerController0);
	this->DisableInput(PlayerController1);
}

void APlayerCharacter::IncreaseSpeed_Implementation()
{
	// increae our max walking speed my 50
	UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent)
		MovementComponent->MaxWalkSpeed += 50;
}

void APlayerCharacter::IncreaseBombs_Implementation()
{
	// increase max number of bombs
	++MaxBombs;
}

void APlayerCharacter::IncreaseExplosion_Implementation()
{
	// increase damage radius of our bombs
	ExplosionLength += 100;
}

void APlayerCharacter::DropBomb_Implementation()
{
	FVector Location = GetActorLocation();

	// snap location to nearest center of square
	Location.X = FMath::RoundToInt(Location.X / 100.0f) * 100.0f;
	Location.Y = FMath::RoundToInt(Location.Y / 100.0f) * 100.0f;
	Location.Z = 55.0f;

	if (NumBombs < MaxBombs)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		GetWorld()->SpawnActor<ABomb>(Location, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo)->ExplosionLength = ExplosionLength;
		NumBombs++;
	}
}

void APlayerCharacter::BombExploded_Implementation()
{
	// decrement count when bomb has exploded
	--NumBombs;
}

// handle player1 movement up/down input axis
void APlayerCharacter::Player1MoveUp(float AxisValue)
{
	AddMovementInput(FVector(1, 0, 0), AxisValue);
	if (AxisValue > 0)
		SetActorRotation(FRotator(0, -90, 0));
	else if (AxisValue < 0)
		SetActorRotation(FRotator(0, 90, 0));
}

// handle player1 movement left/right input axis
void APlayerCharacter::Player1MoveRight(float AxisValue)
{
	AddMovementInput(FVector(0, 1, 0), AxisValue);
	if (AxisValue > 0)
		SetActorRotation(FRotator(0, 0, 0));
	else if (AxisValue < 0)
		SetActorRotation(FRotator(0, 180, 0));
}
	
// handle player1 drop bomb input action
void APlayerCharacter::Player1DropBomb()
{
	DropBomb_Implementation();
}

// handle player2 movement up/down input axis
void APlayerCharacter::Player2MoveUp(float AxisValue)
{
	// redirect input to player 2
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 1);
	if (PlayerController)
	{
		APawn* Pawn = PlayerController->GetPawnOrSpectator();
		if (Pawn)
		{
			APlayerCharacter *Character = Cast<APlayerCharacter>(Pawn);
			if (Character)
				Character->Player1MoveUp(AxisValue);
		}
	}
}

// handle player2 movement left/right input axis
void APlayerCharacter::Player2MoveRight(float AxisValue)
{
	// redirect input to player 2
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 1);
	if (PlayerController)
	{
		APawn* Pawn = PlayerController->GetPawnOrSpectator();
		if (Pawn)
		{
			APlayerCharacter *Character = Cast<APlayerCharacter>(Pawn);
			if (Character)
				Character->Player1MoveRight(AxisValue);
		}
	}
}

// handle player2 drop bomb input action
void APlayerCharacter::Player2DropBomb()
{
	// redirect input to player 2
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 1);
	if (PlayerController)
	{
		APawn* Pawn = PlayerController->GetPawnOrSpectator();

		// tell other actor to drop a bomb
		if (Pawn->GetClass()->ImplementsInterface(UBombInterface::StaticClass()))
			IBombInterface::Execute_DropBomb(Pawn);
	}
}