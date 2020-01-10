// Fill out your copyright notice in the Description page of Project Settings.

#include "BPlayerState.h"
#include "BGameState.h"
#include "Net/UnrealNetwork.h"

ABPlayerState::ABPlayerState()
{
	TeamNumber = 0;
	Goals = 0;
	OwnGoals = 0;
	Saves = 0;
}

void ABPlayerState::Reset()
{
	Super::Reset();

	Goals = 0;
	OwnGoals = 0;
	Saves = 0;
}

void ABPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABPlayerState, TeamNumber, COND_None);
	DOREPLIFETIME_CONDITION(ABPlayerState, Goals, COND_None);
	DOREPLIFETIME_CONDITION(ABPlayerState, OwnGoals, COND_None);
	DOREPLIFETIME_CONDITION(ABPlayerState, Saves, COND_None);
}

void ABPlayerState::K2_SetPlayerName(const FString& NewPlayerName)
{
	SetPlayerName(NewPlayerName);
}

void ABPlayerState::SetTeamNumber(int32 NewTeamNumber)
{
	TeamNumber = NewTeamNumber;
}

void ABPlayerState::ScoreGoal(ABPlayerState* ScoredBy, int32 Points) 
{
	Goals++;
	Score += Points;
}

void ABPlayerState::ScoreOwnGoal(ABPlayerState* ScoredBy, int32 Points)
{
	OwnGoals++;
	Score -= Points;
}

void ABPlayerState::ScoreSave(ABPlayerState* ScoredBy, int32 Points)
{
	Saves++;
	Score += Points;
}

int32 ABPlayerState::GetTeamNumber() const
{
	return TeamNumber;
}

int32 ABPlayerState::GetGoals() const
{
	return Goals;
}

int32 ABPlayerState::GetOwnGoals() const
{
	return OwnGoals;
}

int32 ABPlayerState::GetSaves() const
{
	return Saves;
}

float ABPlayerState::GetScore() const
{
	return Score;
}
