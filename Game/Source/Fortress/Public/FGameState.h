// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FGameState.generated.h"

UCLASS()
class FORTRESS_API AFGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AFGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Number of teams allowed in a game */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 NumTeams;

	/** Time left for game */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 RemainingTime;

	/** Accumulated blue team score */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 BlueTeamScore;

	/** Accumulated red team score */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 RedTeamScore;
};
