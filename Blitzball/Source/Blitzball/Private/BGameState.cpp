// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameState.h"
#include "Net/UnrealNetwork.h"

ABGameState::ABGameState()
{
	NumTeams = 0;
	RemainingTime = 0;
}

void ABGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABGameState, NumTeams, COND_None);
	DOREPLIFETIME_CONDITION(ABGameState, RemainingTime, COND_None);
	DOREPLIFETIME_CONDITION(ABGameState, RedTeamGoals, COND_None);
	DOREPLIFETIME_CONDITION(ABGameState, BlueTeamGoals, COND_None);
}
