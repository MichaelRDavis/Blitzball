// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameMode.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "BGameState.h"
#include "BCharacter.h"

ABGameMode::ABGameMode()
{
	PlayerControllerClass = ABPlayerController::StaticClass();
	PlayerStateClass = ABPlayerState::StaticClass();
	GameStateClass = ABGameState::StaticClass();

	NumTeams = 2;
	WinningTeam = 0;
}

void ABGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorld()->GetTimerManager().SetTimer(MatchTimer, this, &ABGameMode::StartMatchTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void ABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABPlayerState* PlayerState = Cast<ABPlayerState>(NewPlayer->PlayerState);
	const int32 TeamNumber = ChooseTeam(PlayerState);
	PlayerState->SetTeamNumber(TeamNumber);

	Super::PostLogin(NewPlayer);
}

UClass* ABGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	ABPlayerController* PlayerController = Cast<ABPlayerController>(InController);
	if (PlayerController)
	{
		return DefaultCharacterClass;
	}

	return DefaultPawnClass;
}

AActor* ABGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}

void ABGameMode::StartMatchTimer()
{
	if (GetWorld()->IsPlayInEditor())
	{
		if (GetMatchState() == MatchState::WaitingToStart)
		{
			StartMatch();
		}

		return;
	}

	ABGameState* const Game = Cast<ABGameState>(GameState);
	if (Game && Game->RemainingTime > 0)
	{
		if (Game->RemainingTime <= 0)
		{
			if (GetMatchState() == MatchState::WaitingPostMatch)
			{
				RestartGame();
			}
			else if (GetMatchState() == MatchState::InProgress)
			{
				EndMatch();
			}
			else if (GetMatchState() == MatchState::WaitingToStart)
			{
				StartMatch();
			}
		}
	}
}

int32 ABGameMode::ChooseTeam(ABPlayerState* PlayerState) const
{
	TArray<int32> TeamBalance;
	TeamBalance.AddZeroed(NumTeams);

	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		ABPlayerState* Player = Cast<ABPlayerState>(GameState->PlayerArray[i]);
		if (Player && Player != PlayerState && TeamBalance.IsValidIndex(Player->GetTeamNumber()))
		{
			TeamBalance[Player->GetTeamNumber()]++;
		}
	}

	int32 BestTeam = TeamBalance[0];
	for (int32 i = 1; i < TeamBalance.Num(); i++)
	{
		if (BestTeam > TeamBalance[i])
		{
			BestTeam = TeamBalance[i];
		}
	}

	TArray<int32> BestTeams;
	for (int32 i = 0; i < TeamBalance.Num(); i++)
	{
		if (TeamBalance[i] == BestTeam)
		{
			BestTeams.Add(i);
		}
	}

	const int32 RandomBestTeam = BestTeams[FMath::RandHelper(BestTeams.Num())];
	return RandomBestTeam;
}

void ABGameMode::DetermineMatchWinner()
{

}

bool ABGameMode::IsWinner() const
{
	return true;
}
