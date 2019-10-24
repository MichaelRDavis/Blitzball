// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickup.h"
#include "FPickup_Powerup.generated.h"

UCLASS()
class FORTRESS_API AFPickup_Powerup : public AFPickup
{
	GENERATED_BODY()

public:
	AFPickup_Powerup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Powerup)
	float RemainingTime;

	virtual void GiveTo(AFCharacter* Pawn) override;
};
