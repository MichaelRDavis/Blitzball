// Fill out your copyright notice in the Description page of Project Settings.

#include "BBlitzball.h"
#include "BCharacter.h"
#include "BPlayerState.h"
#include "BBlitzballBase.h"
#include "BGoal.h"
#include "BGameState.h"
#include "BGameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#define BLITZBALL_HIGHLIGHT 255

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

void ABBlitzball::OnBeginFocus()
{
	BlitzballMesh->SetRenderCustomDepth(true);
	BlitzballMesh->SetCustomDepthStencilValue(BLITZBALL_HIGHLIGHT);
}

void ABBlitzball::OnEndFocus()
{
	BlitzballMesh->SetRenderCustomDepth(false);
	BlitzballMesh->SetCustomDepthStencilValue(0);
}

void ABBlitzball::SetLastPlayer(ABCharacter* NewPlayer)
{
	Pawn = NewPlayer;
	Player = Cast<ABPlayerState>(NewPlayer->GetPlayerState());
	HitTime = GetWorld()->GetTimeSeconds();
}

void ABBlitzball::Score(ABGoal* Goal)
{
	ABGameState* Game = Cast<ABGameState>(GetWorld()->GetGameState());
	if (Player && Game)
	{
		if (Player->GetTeamNumber() != Goal->GetTeamNumber())
		{
			if (Player->GetTeamNumber() == 0)
			{
				Game->BlueTeamGoals++;
			}
			else if(Player->GetTeamNumber() == 1)
			{
				Game->RedTeamGoals++;
			}

			Player->ScoreGoal(Player, 100);
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

			Player->ScoreOwnGoal(Player, 100);
		}
	}

	ABGameMode* GameMode = Cast<ABGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->RestartMatch();
	}
}

void ABBlitzball::SpawnAtBase()
{
	if (HomeBase)
	{
		HomeBase->ServerSpawnBlitzball();
	}
}
