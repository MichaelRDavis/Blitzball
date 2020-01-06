// Fill out your copyright notice in the Description page of Project Settings.

#include "BTeamPlayerStart.h"

ABTeamPlayerStart::ABTeamPlayerStart(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ABTeamPlayerStart::SetSpawnTeam(int32 NewSpawnTeam)
{
	SpawnTeam = NewSpawnTeam;
}
