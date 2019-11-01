// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FGameMode.generated.h"

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

	virtual void Killled(AController* Killer, AController KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType);

	void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = Classes)
	TSubclassOf<AFCharacter> CharacterClass;

	UPROPERTY()
	int32 MatchTime;

	/** Number of teams allowed in game */
	UPROPERTY()
	int32 NumTeams;

	/** Best team */
	UPROPERTY()
	int32 WinningTeam;

	/** Pick a random team */
	int32 ChooseTeam(AFPlayerState* PlayerState) const;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GameMode)
	//int32 MonsterCount;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GameMode)
	//int32 CurrentWave;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	//float WaveCooldownTime;

	//UFUNCTION(BlueprintCallable, Category = GameMode)
	//void SpawnMonster();

	//FTimerHandle SpawnTimer;
	//FTimerHandle WaveTimer;
};
