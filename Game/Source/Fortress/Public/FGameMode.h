// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FGameMode.generated.h"

class APlayerStart;
class AFCharacter;
class AFPlayerState;

UCLASS(config=Game)
class FORTRESS_API AFGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AFGameMode();

	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/** Character class to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = Classes)
	TSubclassOf<AFCharacter> CharacterClass;

	/** Match duration */
	UPROPERTY()
	int32 MatchTime;

	/** Timer for match */
	FTimerHandle MatchTimer;

	/** Number of teams allowed in game */
	UPROPERTY()
	int32 NumTeams;

	/** Best team */
	UPROPERTY()
	int32 WinningTeam;

	/** Pick a random team */
	UFUNCTION(BlueprintCallable, Category = GameMode)
	int32 ChooseTeam(AFPlayerState* PlayerState) const;

	/** Check if player can use spawn point */
	UFUNCTION(BlueprintCallable, Category = GameMode)
	virtual bool CanSpawn(APlayerStart* SpawnPoint, AController* Player) const;
};
