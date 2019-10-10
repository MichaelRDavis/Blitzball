// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerController.h"
#include "FCharacter.h"

AFPlayerController::AFPlayerController()
{

}

void AFPlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);
	FCharacter = Cast<AFCharacter>(InPawn);
}

void AFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFPlayerController::MoveForward);
	InputComponent->BindAxis("MoveBackward", this, &AFPlayerController::MoveBackward);
	InputComponent->BindAxis("MoveRight", this, &AFPlayerController::MoveRight);
	InputComponent->BindAxis("MoveLeft", this, &AFPlayerController::MoveLeft);
	InputComponent->BindAxis("Turn", this, &AFPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPlayerController::AddPitchInput);
}

void AFPlayerController::MoveForward(float Value)
{

}

void AFPlayerController::MoveBackward(float Value)
{

}

void AFPlayerController::MoveRight(float Value)
{

}

void AFPlayerController::MoveLeft(float Value)
{

}
