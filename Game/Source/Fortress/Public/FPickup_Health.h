// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickup.h"
#include "FPickup_Health.generated.h"

UCLASS()
class FORTRESS_API AFPickup_Health : public AFPickup
{
	GENERATED_BODY()
	
public:
	AFPickup_Health();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 HealthAmount;

	void GiveTo(AFCharacter* Pawn) override;
};
