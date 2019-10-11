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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	/** Weapon mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxMagazineSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 InitialMagazines;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = Weapon)
	int32 Ammo;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = Weapon)
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FName HandsAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Spread;

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void StartFire();
	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AttachToOwner();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void DetachFromOwner();
};
