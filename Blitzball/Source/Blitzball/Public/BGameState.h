// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BGameState.generated.h"

UCLASS()
class BLITZBALL_API ABGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ABGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 NumTeams;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 RedTeamGoals;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 BlueTeamGoals;
};
