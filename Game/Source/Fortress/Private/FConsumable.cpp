// Fill out your copyright notice in the Description page of Project Settings.

#include "FConsumable.h"
#include "TimerManager.h"

AFConsumable::AFConsumable()
{
	UseTime = 2.0f;
}

void AFConsumable::Destroyed()
{
	Super::Destroyed();

	GetWorldTimerManager().ClearTimer(UseTimer);
}

void AFConsumable::Use_Implementation()
{
	
}

void AFConsumable::StartUseTimer()
{
	GetWorldTimerManager().SetTimer(UseTimer, this, &AFConsumable::Use, UseTime, false);
}
