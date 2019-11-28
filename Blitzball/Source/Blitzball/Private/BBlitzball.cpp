// Fill out your copyright notice in the Description page of Project Settings.

#include "BBlitzball.h"
#include "BCharacter.h"
#include "BPlayerState.h"
#include "BBlitzballBase.h"
#include "BGoal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABBlitzball::ABBlitzball()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->SetupAttachment(GetRootComponent());
	CollisionComp->SetSimulatePhysics(true);

	BlitzballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	BlitzballMesh->SetupAttachment(CollisionComp);

	GoalScore = 100;

	SetReplicates(true);
	bReplicateMovement = true;
}

void ABBlitzball::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ABBlitzball::SetLastPlayer(ABCharacter* NewPlayer)
{
	Pawn = NewPlayer;
	Player = Cast<ABPlayerState>(NewPlayer->GetPlayerState());
	HitTime = GetWorld()->GetTimeSeconds();
}

void ABBlitzball::Score(ABGoal* Goal)
{
	if (Player)
	{
		if (Player->GetTeamNumber() != Goal->GetTeamNumber())
		{
			Player->ScoreGoal(Player, GoalScore);
		}
		else
		{
			Player->ScoreGoal(Player, -GoalScore);
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
