// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerState.h"
#include "Net/UnrealNetwork.h"

AFPlayerState::AFPlayerState()
{
	TeamNumber = 0;
	Kills = 0;
	Deaths = 0;
}

void AFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFPlayerState, Kills, COND_None);
	DOREPLIFETIME_CONDITION(AFPlayerState, Deaths, COND_None);
	DOREPLIFETIME_CONDITION(AFPlayerState, TeamNumber, COND_None);
}

void AFPlayerState::Reset()
{
	Super::Reset();

	TeamNumber = 0;
	Kills = 0;
	Deaths = 0;
}

void AFPlayerState::AddKill(int32 Points)
{
	Kills++;
	ScorePoints(Points);
}

void AFPlayerState::AddDeath(int32 Points)
{
	Deaths++;
	ScorePoints(Points);
}

void AFPlayerState::SetTeamNumber(int32 NewTeamNumber)
{
	TeamNumber = NewTeamNumber;
}

int32 AFPlayerState::GetTeamNumber() const
{
	return TeamNumber;
}

int32 AFPlayerState::GetKills() const
{
	return Kills;
}

int32 AFPlayerState::GetDeaths() const
{
	return Deaths;
}

float AFPlayerState::GetScore() const
{
	return Score;
}

void AFPlayerState::ScorePoints(int32 Points)
{
	Score += Points;
}
