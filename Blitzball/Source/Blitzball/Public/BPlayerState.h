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

	void SetTeamNumber(int32 NewTeamNumber);

	void ScoreGoal(ABPlayerState* ScoredBy, int32 Points);

	void ScoreOwnGoal(ABPlayerState* ScoredBy, int32 Points);

	UFUNCTION(BlueprintCallable, Category=PlayerState)
	void ScoreSave(ABPlayerState* ScoredBy, int32 Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetTeamNumber() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetGoals() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetOwnGoals() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetSaves() const;

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
};
