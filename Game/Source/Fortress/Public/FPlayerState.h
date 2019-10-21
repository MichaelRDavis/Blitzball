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

protected:
	/** Number of kills */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Kills;

	/** Number of deaths */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Deaths;

	/** Max number of lives */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerState)
	int32 MaxLives;

	/** Current number of lives */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = PlayerState)
	int32 Lives;
};
