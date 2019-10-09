// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.h"
#include "FWeapon.generated.h"

UENUM()
enum class EWeaponState 
{
	EIdle,
	EFiring,
	EReloading,
	EEquiping
};

UENUM()
enum class EAmmoType
{
	EBullet UMETA(DisplayName = "Bullet"),
	EEnergy UMETA(DisplayName = "Energy"),
	EShells UMETA(DisplayName = "Shells"),
	ERockets UMETA(DisplayName = "Rockets"),
	EGrenades UMETA(DisplayName = "Grenades")
};

UCLASS()
class FORTRESS_API AFWeapon : public AFInventoryItem
{
	GENERATED_BODY()

public:
	AFWeapon();

	/** Weapon mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Mesh;
};
