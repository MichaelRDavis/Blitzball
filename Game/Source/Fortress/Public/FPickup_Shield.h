// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickup.h"
#include "FPickup_Shield.generated.h"

UCLASS()
class FORTRESS_API AFPickup_Shield : public AFPickup
{
	GENERATED_BODY()
	
public:
	AFPickup_Shield();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 ShieldAmount;

	void GiveTo(AFCharacter* Pawn) override;
};
