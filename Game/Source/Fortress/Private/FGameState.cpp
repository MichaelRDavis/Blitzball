// Fill out your copyright notice in the Description page of Project Settings.

#include "FGameState.h"
#include "Net/UnrealNetwork.h"

AFGameState::AFGameState()
{
	NumTeams = 0;
	RemainingTime = 0;
}

void AFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFGameState, NumTeams, COND_None);
	DOREPLIFETIME_CONDITION(AFGameState, RemainingTime, COND_None);
}
