// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FGameMode.generated.h"

class AFCharacter;

UCLASS()
class FORTRESS_API AFGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AFGameMode();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = Classes)
	TSubclassOf<AFCharacter> CharacterClass;
};
