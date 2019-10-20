// Fill out your copyright notice in the Description page of Project Settings.

#include "FGameMode.h"
#include "FPlayerController.h"
#include "FPlayerState.h"
#include "FCharacter.h"

AFGameMode::AFGameMode()
{
	PlayerControllerClass = AFPlayerController::StaticClass();
	PlayerStateClass = AFPlayerState::StaticClass();
}

void AFGameMode::StartPlay()
{
	Super::StartPlay();
}

void AFGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UClass* AFGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	AFPlayerController* PlayerController = Cast<AFPlayerController>(InController);
	if (PlayerController)
	{
		return CharacterClass;
	}

	return DefaultPawnClass;
}

void AFGameMode::SpawnMonster()
{

}
