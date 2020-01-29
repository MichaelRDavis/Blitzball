// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameMode.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "BGameState.h"
#include "BCharacter.h"
#include "BTeamPlayerStart.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/PlayerStartPIE.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"

ABGameMode::ABGameMode()
{
	PlayerControllerClass = ABPlayerController::StaticClass();
	PlayerStateClass = ABPlayerState::StaticClass();
	GameStateClass = ABGameState::StaticClass();

	NumTeams = 2;
	WinningTeam = 0;
	bIsMatchDraw = false;
	WarmupTime = 15;
	MatchTime = 300;
	TimeBetweenMatches = 15;
	GoalScore = 50;
	SaveScore = 25;
	WinScore = 500;
	DrawScore = 250;
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

	// Notify new players that the match is in progress

	Super::PostLogin(NewPlayer);
}

void ABGameMode::InitGameState()
{
	ABGameState* const BGameState = Cast<ABGameState>(GameState);
	if (GameState)
	{
		BGameState->NumTeams = NumTeams;
	}
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
	TArray<APlayerStart*> PreferredStarts;

	APlayerStart* BestStart = nullptr;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* TestStart = *It;
		if (TestStart->IsA<APlayerStartPIE>())
		{
			BestStart = TestStart;
			break;
		}
		else
		{
			if (IsSpawnPointAllowed(TestStart, Player))
			{
				PreferredStarts.Add(TestStart);
			}
		}
	}

	if (BestStart == nullptr)
	{
		if (PreferredStarts.Num() > 0)
		{
			BestStart = PreferredStarts[FMath::RandHelper(PreferredStarts.Num())];
		}
	}

	return BestStart;
}

void ABGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
}

void ABGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	ABGameState* BGameState = Cast<ABGameState>(GameState);
	BGameState->RemainingTime = MatchTime;
}

void ABGameMode::RestartPlayer(AController* NewPlayer)
{
	ChoosePlayerStart_Implementation(NewPlayer);

	Super::RestartPlayer(NewPlayer);
}

void ABGameMode::StartMatch()
{
	Super::StartMatch();

	if (StartMatchSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), StartMatchSound);
	}
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
		Game->RemainingTime--;

		if (Game->RemainingTime <= 0)
		{
			if (GetMatchState() == MatchState::WaitingPostMatch)
			{
				RestartGame();
			}
			else if (GetMatchState() == MatchState::InProgress)
			{
				FinishMatch();

				// Notify the player that the match has ended
				for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
				{

				}
			}
			else if (GetMatchState() == MatchState::WaitingToStart)
			{
				StartMatch();
			}
		}
	}
}

void ABGameMode::RestartMatch()
{
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		ABPlayerState* Player = Cast<ABPlayerState>(GameState->PlayerArray[i]);
		if (Player)
		{
			ABPlayerController* Controller = Cast<ABPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
			RestartPlayer(Controller);
		}
	}
}

void ABGameMode::FinishMatch()
{
	ABGameState* const BGameState = Cast<ABGameState>(GameState);

	if (IsMatchInProgress())
	{
		EndMatch();
		DetermineMatchWinner();

		// Notify all players of match end
		for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
		{
			
		}

		// Lock all pawns
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		if (EndMatchWidget)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), EndMatchWidget);
			if (CurrentWidget)
			{
				CurrentWidget->AddToViewport();
			}
		}

		BGameState->RemainingTime = TimeBetweenMatches;
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
	ABGameState const* const BGameState = Cast<ABGameState>(GameState);
	if (BGameState->RedTeamGoals > BGameState->BlueTeamGoals)
	{
		WinningTeam = 1;
	}
	else if (BGameState->BlueTeamGoals > BGameState->RedTeamGoals)
	{
		WinningTeam = 0;
	}
	else if (BGameState->BlueTeamGoals == BGameState->RedTeamGoals)
	{
		WinningTeam = 0;
		bIsMatchDraw = true;
	}
}

void ABGameMode::RewardEndMatchScore()
{
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		ABPlayerState* PlayerState = Cast<ABPlayerState>(GameState->PlayerArray[i]);
		if (PlayerState)
		{
			if (IsWinner(PlayerState))
			{
				// TODO: Add win score to player score
			}
		}
	}
}

bool ABGameMode::IsSpawnPointAllowed(APlayerStart* Start, AController* Player) const
{
	if (Player)
	{
		ABTeamPlayerStart* TeamStart = Cast<ABTeamPlayerStart>(Start);
		ABPlayerState* PlayerState = Cast<ABPlayerState>(Player->PlayerState);

		if (PlayerState && TeamStart && TeamStart->SpawnTeam == PlayerState->GetTeamNumber())
		{
			return true;
		}
	}

	return false;
}

bool ABGameMode::IsWinner(ABPlayerState* PlayerState) const
{
	return PlayerState && PlayerState->GetTeamNumber() == WinningTeam;
}
