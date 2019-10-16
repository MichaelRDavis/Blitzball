// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWeapon.h"
#include "FWeap_Shotgun.generated.h"

UCLASS()
class FORTRESS_API AFWeap_Shotgun : public AFWeapon
{
	GENERATED_BODY()

public:
	AFWeap_Shotgun();

	void Fire();
};
