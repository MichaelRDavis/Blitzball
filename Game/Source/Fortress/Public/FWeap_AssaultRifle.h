// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWeapon.h"
#include "FWeap_AssaultRifle.generated.h"

UCLASS()
class FORTRESS_API AFWeap_AssaultRifle : public AFWeapon
{
	GENERATED_BODY()
	
public:
	AFWeap_AssaultRifle();

	void Fire();
};
