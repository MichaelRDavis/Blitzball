// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FWeapon.h"
#include "FInventoryItem.h"
#include "FAmmo.generated.h"

UCLASS()
class FORTRESS_API AFAmmo : public AFInventoryItem
{
	GENERATED_BODY()
	
public:
	AFAmmo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	int32 AmmoRestored;
};
