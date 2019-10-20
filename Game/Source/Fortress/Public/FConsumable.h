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

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	void Use();
	void Use_Implementation();

	UFUNCTION(BlueprintCallable, Category = Iventory)
	void StartUseTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	USoundCue* UseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	float UseTime;

	FTimerHandle UseTimer;
};
