// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPlayerState.generated.h"

UCLASS()
class FORTRESS_API AFPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AFPlayerState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Reset() override;

	/** Player killed an opponent */
	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void AddKill(int32 Points);

	/** Player died */
	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void AddDeath(int32 Points);

	/** Set players team number */
	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void SetTeamNumber(int32 NewTeamNumber);

	/** Get players team number */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetTeamNumber() const;

	/** Get number of kills */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetKills() const;

	/** Get number of deaths */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	int32 GetDeaths() const;

	/** Get player score */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = PlayerState)
	float GetScore() const;

protected:
	/** Team number assigned to player */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 TeamNumber;

	/** Number of kills */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Kills;

	/** Number of deaths */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Deaths;

	/** Add to player score */
	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void ScorePoints(int32 Points);
};
