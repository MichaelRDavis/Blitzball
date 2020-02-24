// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BPlayerState.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	ERed = 0,
	EBlue = 1
};

UCLASS()
class BLITZBALL_API ABPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ABPlayerState();

	virtual void Reset() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void SetTeamNumber(int32 NewTeamNumber);

	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void AddScore(int32 Points);

	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void ScoreGoal(ABPlayerState* ScoredBy, int32 Points);

	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void ScoreOwnGoal(ABPlayerState* ScoredBy, int32 Points);

	UFUNCTION(BlueprintCallable, Category=PlayerState)
	void ScoreSave(ABPlayerState* ScoredBy, int32 Points);

	UFUNCTION(BlueprintCallable, Category = PLayerState)
	void ScoreAssist(ABPlayerState* ScoredBy, ABPlayerState* LastPlayer, int32 Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetTeamNumber() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetGoals() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetOwnGoals() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetSaves() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=PlayerState)
	int32 GetAssists() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=PlayerState)
	int32 GetMatchesPlayed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=PlayerState)
	int32 GetMatchesWon() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=PlayerState)
	int32 GetMatchesLost() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=PlayerState)
	int32 GetMatchesDrawn() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	float GetScore() const;

protected:
	UPROPERTY(Replicated)
	int32 TeamNumber;

	UPROPERTY(Replicated)
	int32 Goals;

	UPROPERTY(Replicated)
	int32 OwnGoals;

	UPROPERTY(Replicated)
	int32 Saves;

	UPROPERTY(Replicated)
	int32 Assist;

	UPROPERTY(Replicated)
	int32 MatchesPlayed;

	UPROPERTY(Replicated)
	int32 MatchesWon;

	UPROPERTY(Replicated)
	int32 MatchesLost;

	UPROPERTY(Replicated)
	int32 MatchesDraw;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxLevel;

	UPROPERTY(BlueprintReadOnly)
	int32 XP;

	UPROPERTY(BlueprintReadOnly)
	int32 XPToNextLevel;

	UPROPERTY(BlueprintReadOnly)
	int32 XPLevelMultiplier;
};
