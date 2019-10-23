// Fill out your copyright notice in the Description page of Project Settings.

#include "FPickup_Health.h"
#include "FCharacter.h"

AFPickup_Health::AFPickup_Health()
{
	HealthAmount = 25;
}

void AFPickup_Health::GiveTo(AFCharacter* Pawn)
{
	if (Pawn)
	{
		Pawn->Health = FMath::Min(FMath::TruncToInt(Pawn->Health) + HealthAmount, Pawn->GetMaxHealth());
	}
}
