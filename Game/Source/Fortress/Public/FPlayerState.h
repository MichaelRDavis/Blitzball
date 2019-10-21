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

	UFUNCTION(BlueprintCallable, Category = Player)
	void LevelUp(int32 AddXP);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Player)
	int32 PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	int32 MaxPlayerLevel;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Player)
	int32 CurrentXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	int32 LevelUpXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	int32 LevelMultiplier;

	/** Number of kills */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Kills;

	/** Number of deaths */
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Deaths;
};
