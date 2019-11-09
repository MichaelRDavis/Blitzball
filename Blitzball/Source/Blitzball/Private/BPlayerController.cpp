// Fill out your copyright notice in the Description page of Project Settings.

#include "BPlayerController.h"
#include "BCharacter.h"

ABPlayerController::ABPlayerController()
{
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
}

void ABPlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);
	BCharacter = Cast<ABCharacter>(InPawn);
}

void ABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABPlayerController::MoveForward);
	InputComponent->BindAxis("MoveBackward", this, &ABPlayerController::MoveBackward);
	InputComponent->BindAxis("MoveRight", this, &ABPlayerController::MoveRight);
	InputComponent->BindAxis("MoveLeft", this, &ABPlayerController::MoveLeft);
	InputComponent->BindAxis("Turn", this, &ABPlayerController::AddYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &ABPlayerController::AddPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABPlayerController::LookUpAtRate);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABPlayerController::OnJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABPlayerController::OnStopJumping);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ABPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ABPlayerController::OnStopFire);
}

void ABPlayerController::MoveForward(float Value)
{
	if (BCharacter != nullptr && Value != 0.0f)
	{
		BCharacter->MoveForward(Value);
	}
}

void ABPlayerController::MoveBackward(float Value)
{
	MoveForward(Value * -1);
}

void ABPlayerController::MoveRight(float Value)
{
	if (BCharacter != nullptr && Value != 0.0f)
	{
		BCharacter->MoveRight(Value);
	}
}

void ABPlayerController::MoveLeft(float Value)
{
	MoveRight(Value * -1);
}

void ABPlayerController::TurnAtRate(float Rate)
{
	AddYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABPlayerController::LookUpAtRate(float Rate)
{
	AddPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABPlayerController::OnJump()
{
	if (BCharacter)
	{
		BCharacter->Jump();
	}
}

void ABPlayerController::OnStopJumping()
{
	if (BCharacter)
	{
		BCharacter->StopJumping();
	}
}

void ABPlayerController::OnStartFire()
{
	if (BCharacter)
	{
		BCharacter->StartFire();
	}
}

void ABPlayerController::OnStopFire()
{
	if (BCharacter)
	{
		BCharacter->StopFire();
	}
}
