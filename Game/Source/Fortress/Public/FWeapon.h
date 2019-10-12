// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.h"
#include "FWeapon.generated.h"

class AFProjectile;

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

USTRUCT(BlueprintType)
struct FInstantHitDamageInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
};

UCLASS(Abstract, Blueprintable, config=Game)
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
	int32 AmmoCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<AFProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FInstantHitDamageInfo InstantHitInfo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	EWeaponState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FName HandsAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxTracerRange;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void OnEquip();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void UnEquip();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void StartFire();
	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void StopFire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartFire();
	void ServerStartFire_Implementation();
	bool ServerStartFire_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStopFire();
	void ServerStopFire_Implementation();
	bool ServerStopFire_Validate();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void FireInstantHit();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void FireProjectile();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AttachToOwner();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void DetachFromOwner();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetAdjustedAim() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetFireStartLocation(const FVector& AimDir) const;

	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector TraceTo) const;
};
