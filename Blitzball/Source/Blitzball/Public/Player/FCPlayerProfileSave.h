// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FCPlayerProfileSave.generated.h"

class ABPlayerState;

UCLASS()
class BLITZBALL_API UFCPlayerProfileSave : public USaveGame
{
	GENERATED_BODY()

public:
	UFCPlayerProfileSave();

	UFUNCTION(BlueprintCallable, Category=SaveGame)
	static UFCPlayerProfileSave* LoadPlayerProfileData(FString SlotName, const int32 UserIndex);
	
	UFUNCTION(BlueprintCallable, Category=SaveGame)
	void SavePlayerProfileData();

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	void SaveIfDirty();

	UFUNCTION(BlueprintCallable)
	void SetPlayerProfileName(FString InPlayerProfileName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetPlayerProfileName() const;

	void AddMatchResult(ABPlayerState* PlayerState);

protected:
	UPROPERTY()
	FString PlayerProfileName;

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Goals;

	UPROPERTY()
	int32 Saves;

	UPROPERTY()
	int32 Assists;

	UPROPERTY()
	int32 MatchWins;

	UPROPERTY()
	int32 MatchLosses;

	UPROPERTY()
	int32 MatchesDraw;

	UPROPERTY()
	int32 MatchesPlayed;

private:
	bool bIsDirty;
	FString SlotName;
	int32 UserIndex;
};
