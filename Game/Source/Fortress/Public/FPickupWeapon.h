// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickupItem.h"
#include "FPickupWeapon.generated.h"

UCLASS()
class FORTRESS_API AFPickupWeapon : public AFPickupItem
{
	GENERATED_BODY()
	
public:
	AFPickupWeapon();

	void OnUsed_Implementation(AFCharacter* Character);
	void OnBeginFocus_Implementation();
	void OnEndFocus_Implementation();
};
