// Fill out your copyright notice in the Description page of Project Settings.

#include "BMenuGameMode.h"
#include "BMenuPlayerController.h"

ABMenuGameMode::ABMenuGameMode()
{
	PlayerControllerClass = ABMenuPlayerController::StaticClass();
}
