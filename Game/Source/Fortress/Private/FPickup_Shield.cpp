// Fill out your copyright notice in the Description page of Project Settings.

#include "FPickup_Shield.h"
#include "FCharacter.h"

AFPickup_Shield::AFPickup_Shield()
{
	ShieldAmount = 25;
}

void AFPickup_Shield::GiveTo(AFCharacter* Pawn)
{
	if (Pawn)
	{
		Pawn->Shield = FMath::Min(FMath::TruncToInt(Pawn->Shield) + ShieldAmount, Pawn->MaxShield);
	}
}
