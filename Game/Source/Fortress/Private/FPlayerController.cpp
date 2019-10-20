// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerController.h"
#include "FCharacter.h"
#include "FPlayerCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AFPlayerController::AFPlayerController()
{
	PlayerCameraManagerClass = AFPlayerCameraManager::StaticClass();
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
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPlayerController::StopJumping);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFPlayerController::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFPlayerController::StopSprinting);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AFPlayerController::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AFPlayerController::UnCrouch);
	InputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &AFPlayerController::ToggleCrouch);

	InputComponent->BindAction("Use", IE_Pressed, this, &AFPlayerController::OnUse);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AFPlayerController::OnStopFire);
	InputComponent->BindAction("Targeting", IE_Pressed, this, &AFPlayerController::OnStartTargeting);
	InputComponent->BindAction("Targeting", IE_Released, this, &AFPlayerController::OnStopTargeting);
	InputComponent->BindAction("Reload", IE_Pressed, this, &AFPlayerController::OnReload);
}

void AFPlayerController::MoveForward(float Value)
{
	if (FCharacter != nullptr && Value != 0.0f)
	{
		FCharacter->MoveForward(Value);
	}
}

void AFPlayerController::MoveBackward(float Value)
{
	MoveForward(Value * -1);
}

void AFPlayerController::MoveRight(float Value)
{
	if (FCharacter != nullptr && Value != 0.0f)
	{
		FCharacter->MoveRight(Value);
	}
}

void AFPlayerController::MoveLeft(float Value)
{
	MoveRight(Value * -1);
}

void AFPlayerController::Jump()
{
	if (FCharacter)
	{
		FCharacter->Jump();
	}
}

void AFPlayerController::StopJumping()
{
	if (FCharacter)
	{
		FCharacter->StopJumping();
	}
}

void AFPlayerController::Sprint()
{
	if (FCharacter)
	{
		FCharacter->Sprint();
	}
}

void AFPlayerController::StopSprinting()
{
	if (FCharacter)
	{
		FCharacter->StopSprinting();
	}
}

void AFPlayerController::Crouch()
{
	if (FCharacter)
	{
		FCharacter->Crouch();
	}
}

void AFPlayerController::UnCrouch()
{
	if (FCharacter)
	{
		FCharacter->UnCrouch();
	}
}

void AFPlayerController::ToggleCrouch()
{
	if (GetCharacter())
	{
		GetCharacter()->bIsCrouched ? UnCrouch() : Crouch();
	}
}

void AFPlayerController::OnUse()
{
	if (FCharacter)
	{
		FCharacter->Use();
	}
}

void AFPlayerController::OnStartFire()
{
	if (FCharacter)
	{
		FCharacter->StartFire();
	}
}

void AFPlayerController::OnStopFire()
{
	if (FCharacter)
	{
		FCharacter->StopFire();
	}
}

void AFPlayerController::OnStartTargeting()
{
	if (FCharacter)
	{
		FCharacter->StartTargeting();
	}
}

void AFPlayerController::OnStopTargeting()
{
	if (FCharacter)
	{
		FCharacter->StopTargeting();
	}
}

void AFPlayerController::OnReload()
{
	if (FCharacter)
	{
		FCharacter->Reload();
	}
}