// Fill out your copyright notice in the Description page of Project Settings.

#include "FGameMode.h"
#include "FPlayerController.h"
#include "FPlayerState.h"
#include "FGameState.h"
#include "FCharacter.h"

AFGameMode::AFGameMode()
{
	PlayerControllerClass = AFPlayerController::StaticClass();
	PlayerStateClass = AFPlayerState::StaticClass();

	NumTeams = 2;
}

void AFGameMode::StartPlay()
{
	Super::StartPlay();
}

void AFGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UClass* AFGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	AFPlayerController* PlayerController = Cast<AFPlayerController>(InController);
	if (PlayerController)
	{
		return CharacterClass;
	}

	return DefaultPawnClass;
}

void AFGameMode::Killled(AController* Killer, AController KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{

}

void AFGameMode::PostLogin(APlayerController* NewPlayer)
{
	AFPlayerState* PlayerState = Cast<AFPlayerState>(NewPlayer->PlayerState);
	const int32 TeamNum = ChooseTeam(PlayerState);
	PlayerState->SetTeamNumber(TeamNum);

	Super::PostLogin(NewPlayer);
}

int32 AFGameMode::ChooseTeam(AFPlayerState* PlayerState) const
{
	TArray<int32> Teams;
	Teams.AddZeroed(NumTeams);

	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		AFPlayerState const* const TestPlayerState = Cast<AFPlayerState>(GameState->PlayerArray[i]);
		if (TestPlayerState && TestPlayerState != PlayerState && Teams.IsValidIndex(TestPlayerState->GetTeamNumber()))
		{
			Teams[TestPlayerState->GetTeamNumber()]++;
		}
	}

	const int32 RandomTeams = Teams[FMath::RandHelper(Teams.Num())];
	return RandomTeams;
}
