// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BGameModeBase.h"
#include "BGameMode.generated.h"

class ABCharacter;

UCLASS()
class BLITZBALL_API ABGameMode : public ABGameModeBase
{
	GENERATED_BODY()
	
public:
	ABGameMode();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<ABCharacter> DefaultCharacterClass;
};
