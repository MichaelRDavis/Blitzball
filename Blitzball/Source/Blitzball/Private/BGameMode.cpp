// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameMode.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "BGameState.h"
#include "BCharacter.h"

ABGameMode::ABGameMode()
{
	PlayerControllerClass = ABPlayerController::StaticClass();
	PlayerStateClass = ABPlayerState::StaticClass();
	GameStateClass = ABGameState::StaticClass();
}

UClass* ABGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	ABPlayerController* PlayerController = Cast<ABPlayerController>(InController);
	if (PlayerController)
	{
		return DefaultCharacterClass;
	}

	return DefaultPawnClass;
}
