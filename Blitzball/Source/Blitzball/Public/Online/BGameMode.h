// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BGameModeBase.h"
#include "BGameMode.generated.h"

class ABCharacter;
class ABPlayerState;
class APlayerStart;

UCLASS()
class BLITZBALL_API ABGameMode : public ABGameModeBase
{
	GENERATED_BODY()
	
public:
	ABGameMode();

	virtual void PreInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void InitGameState() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void RestartPlayer(AController* NewPlayer) override;
	virtual void StartMatch() override;

	UFUNCTION(BlueprintCallable, Category = GameMode)
	void StartMatchTimer();

	UFUNCTION(BlueprintCallable, Category = GameMode)
	void RestartMatch();

	UFUNCTION(BlueprintCallable, Category = GameMode)
	void FinishMatch();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<ABCharacter> DefaultCharacterClass;

	inline int32 GetGoalScore() const
	{
		return GoalScore;
	}

	inline int32 GetSaveScore() const
	{
		return SaveScore;
	}

protected:
	int32 ChooseTeam(ABPlayerState* PlayerState) const;
	void DetermineMatchWinner();
	void RewardEndMatchScore();
	bool IsSpawnPointAllowed(APlayerStart* Start, AController* Player) const;

	UFUNCTION(BlueprintCallable, Category=GameMode)
	bool IsWinner(ABPlayerState* PlayerState) const;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GameMode)
	int32 NumTeams;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GameMode)
	int32 WinningTeam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GameMode)
	bool bIsMatchDraw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	int32 WarmupTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	int32 MatchTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	int32 TimeBetweenMatches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	int32 GoalScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	int32 SaveScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameMode)
	int32 WinScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameMode)
	int32 DrawScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sounds)
	USoundBase* StartMatchSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sounds)
	USoundBase* EndMatchSound;

	FTimerHandle MatchTimer;
};
