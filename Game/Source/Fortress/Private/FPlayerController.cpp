// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerController.h"
#include "FCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPlayerController::StopJumping);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFPlayerController::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFPlayerController::StopSprinting);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AFPlayerController::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AFPlayerController::UnCrouch);
	InputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &AFPlayerController::ToggleCrouch);

	InputComponent->BindAction("Use", IE_Pressed, this, &AFPlayerController::Use);
	InputComponent->BindAction("ShowMenu", IE_Pressed, this, &AFPlayerController::ShowCharacterMenu);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPlayerController::StartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AFPlayerController::StopFire);
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

void AFPlayerController::Use()
{
	if (FCharacter)
	{
		FCharacter->Use();
	}
}

void AFPlayerController::StartFire()
{
	if (FCharacter)
	{
		FCharacter->StartFire();
	}
}

void AFPlayerController::StopFire()
{
	if (FCharacter)
	{
		FCharacter->StopFire();
	}
}

void AFPlayerController::OnReload()
{
	if (FCharacter)
	{
		FCharacter->Reload();
	}
}

void AFPlayerController::ShowCharacterMenu()
{
	if (CharacterMenuClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, CharacterMenuClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, CurrentWidget);
			bShowMouseCursor = true;
		}
	}
}
