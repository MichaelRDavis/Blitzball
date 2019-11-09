// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BPlayerState.generated.h"

UCLASS()
class BLITZBALL_API ABPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ABPlayerState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetTeamNumber(int32 NewTeamNumber);

	void ScoreGoal(ABPlayerState* ScoredBy, int32 Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetTeamNumber();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetGoals();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	float GetScore();

protected:
	UPROPERTY(Replicated)
	int32 TeamNumber;

	UPROPERTY(Replicated)
	int32 Goals;
};
