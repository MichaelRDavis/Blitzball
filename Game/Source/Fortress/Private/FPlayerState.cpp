// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerState.h"

AFPlayerState::AFPlayerState()
{
	PlayerLevel = 0;
	MaxPlayerLevel = 20;
	CurrentXP = 0;
	LevelUpXP = 500;
	LevelMultiplier = 2;
}

void AFPlayerState::LevelUp(int32 AddXP)
{
	if (CurrentXP > LevelUpXP)
	{
		if (PlayerLevel < MaxPlayerLevel)
		{
			PlayerLevel++;
		}
	}
}
