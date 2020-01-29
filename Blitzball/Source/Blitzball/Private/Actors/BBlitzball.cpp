// Fill out your copyright notice in the Description page of Project Settings.

#include "BBlitzball.h"
#include "BCharacter.h"
#include "BPlayerState.h"
#include "BBlitzballBase.h"
#include "BGameState.h"
#include "BGameMode.h"
#include "FCReplicatedPhysicsComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ABBlitzball::ABBlitzball()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->SetupAttachment(GetRootComponent());
	CollisionComp->SetSimulatePhysics(true);

	BlitzballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	BlitzballMesh->SetupAttachment(CollisionComp);

	PhysicsReplication = CreateDefaultSubobject<UFCReplicatedPhysicsComponent>(TEXT("PhysicsReplication"));

	SetReplicates(true);
	NetPriority = 3.0f;
	bReplicateMovement = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ABBlitzball::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABBlitzball, Player, COND_None);
}

void ABBlitzball::SetLastPlayer(ABCharacter* NewPlayer)
{
	Pawn = NewPlayer;
	Player = Cast<ABPlayerState>(NewPlayer->GetPlayerState());
	HitTime = GetWorld()->GetTimeSeconds();
}

void ABBlitzball::Score(int32 TeamNumber)
{
	ABGameState* Game = Cast<ABGameState>(GetWorld()->GetGameState());
	ABGameMode* BGameMode = Cast<ABGameMode>(GetWorld()->GetAuthGameMode());
	if (Player && Game && BGameMode)
	{
		if (Player->GetTeamNumber() != TeamNumber)
		{
			if (Player->GetTeamNumber() == 0)
			{
				Game->BlueTeamGoals++;
			}
			else if(Player->GetTeamNumber() == 1)
			{
				Game->RedTeamGoals++;
			}

			Player->ScoreGoal(Player, BGameMode->GetGoalScore());
		}
		else
		{
			if (Player->GetTeamNumber() == 0)
			{
				Game->RedTeamGoals++;
			}
			else if (Player->GetTeamNumber() == 1)
			{
				Game->BlueTeamGoals++;
			}

			Player->ScoreOwnGoal(Player, BGameMode->GetGoalScore());
		}
	}
}

void ABBlitzball::SpawnAtBase()
{
	if (HomeBase)
	{
		HomeBase->ServerSpawnBlitzball();
	}
}
