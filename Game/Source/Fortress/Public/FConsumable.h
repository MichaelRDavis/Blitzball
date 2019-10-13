// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.h"
#include "FConsumable.generated.h"

class USoundCue;

UCLASS()
class FORTRESS_API AFConsumable : public AFInventoryItem
{
	GENERATED_BODY()
	
public:
	AFConsumable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	void Use(AFCharacter* Character);
	void Use_Implementation(AFCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	USoundCue* UseSound;
};
