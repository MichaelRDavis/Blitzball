// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.h"
#include "FWeapon.generated.h"

class AFProjectile;
class AFAmmo;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EIdle,
	EFiring,
	EReloading,
	EEquiping
};

UENUM(BlueprintType)
enum class EAmmoType : uint8
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

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Weapon mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	/** Max ammo */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxAmmo;
	/** Max magazine size */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxMagazineSize;
	/** Initial magazines */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 InitialMagazines;
	/** Current total ammo */
	UPROPERTY(BlueprintReadWrite, Replicated, Category = Weapon)
	int32 Ammo;
	/** Current ammo inside magazine */
	UPROPERTY(BlueprintReadWrite, Replicated, Category = Weapon)
	int32 MagazineSize;
	/** Ammo cost for one shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 AmmoCost;

	/** Weapon ammo type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool bInfiniteAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool bInfiniteMagazine;

	/** Add ammo */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Weapon)
	virtual void AddAmmo(int32 AddAmount);

	/** Consume ammo */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Weapon)
	virtual void ConsumeAmmo();

	/** Query weapon ammo type */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Weapon)
	virtual EAmmoType GetAmmoType() const
	{
		return AmmoType;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<AFProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FInstantHitDamageInfo InstantHitInfo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	EWeaponState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FName HandsAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FName MuzzleSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxTracerRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Recoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float RecoilRecovery;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsEquipped;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsFiring;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UTexture2D* WeaponCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UAnimMontage* FireAnim;

	UPROPERTY()
	float LastFireTime;

	FTimerHandle FiringTimer;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	bool CanFire() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	bool CanReload() const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void OnEquip();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void UnEquip();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "Fire"))
	void K2_Fire();
	void K2_Fire_Implementation();

	virtual void Fire() PURE_VIRTUAL(AFWeapon::Fire, );

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void FireShot();

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

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StartReload();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StopReload();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartReload();
	void ServerStartReload_Implementation();
	bool ServerStartReload_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStopReload();
	void ServerStopReload_Implementation();
	bool ServerStopReload_Validate();

	virtual void GoToWeaponState(EWeaponState NewWeaponState);
	virtual void UpdateWeaponState();

	virtual void BeginFiring();
	virtual void EndFiring();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void FireInstantHit();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void FireProjectile();

	UFUNCTION(BlueprintCallable, Category = Firing)
	virtual void ApplyRecoil(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void OnHitDamage(FHitResult Hit, const FVector& FireDir);

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnProjectile(FVector Origin, FVector_NetQuantizeNormal ShootDir);
	void SpawnProjectile_Implementation(FVector Origin, FVector_NetQuantizeNormal ShootDir);
	bool SpawnProjectile_Validate(FVector Origin, FVector_NetQuantizeNormal ShootDir);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void PlayFiringEffects();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void PlayWeaponSound(USoundBase* Sound);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void PlayWeaponAnim(UAnimMontage* Anim);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AttachToOwner();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void DetachFromOwner();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetAdjustedAim() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetFireStartLocation(const FVector& AimDir) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetMuzzleLocation() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetMuzzleDirection() const;

	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector TraceTo) const;
};
