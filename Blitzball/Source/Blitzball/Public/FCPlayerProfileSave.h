// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FCPlayerProfileSave.generated.h"

UCLASS()
class BLITZBALL_API UFCPlayerProfileSave : public USaveGame
{
	GENERATED_BODY()

public:
	static UFCPlayerProfileSave* LoadPlayerProfileData(FString SlotName, const int32 UserIndex);
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerProfileName(FString InPlayerProfileName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetPlayerProfileName() const;

	void AddMatchResult(int32 Goals, int32 Saves, bool bIsMatchWinner);

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
	int32 Wins;

	UPROPERTY()
	int32 Losses;

private:
	bool bIsDirty;
	FString SlotName;
	int32 UserIndex;
};
