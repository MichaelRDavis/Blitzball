// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BWeapon.generated.h"

class ABCharacter;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EIdle UMETA(DisplayName="Idle"),
	EFiring UMETA(DisplayName = "Firing"),
};

UCLASS()
class BLITZBALL_API ABWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABWeapon();

	virtual void Tick(float DeltaSeconds) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StartAltFire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StopAltFire();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void AltFire();

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerStartFire();
	virtual void ServerStartFire_Implementation();
	virtual bool ServerStartFire_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerStopFire();
	virtual void ServerStopFire_Implementation();
	virtual bool ServerStopFire_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerStartAltFire();
	virtual void ServerStartAltFire_Implementation();
	virtual bool ServerStartAltFire_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerStopAltFire();
	virtual void ServerStopAltFire_Implementation();
	virtual bool ServerStopAltFire_Validate();

	virtual void GiveTo(ABCharacter* NewOwner);
	virtual void Remove();

	virtual void Equip();
	virtual void UnEquip();

	virtual void SetCanFire();
	virtual void SetCanAltFire();

protected:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Weapon)
	ABCharacter* BOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FName HandsAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float BlitzballImpulseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float PlayerImpulseForce;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bWantsToFire;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bWantsToAltFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireCooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float AltFireCooldownTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsCharging;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsCharged;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Wapon)
	float ChargePercentage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Wapon)
	float ChargeAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	USoundBase* ChargedSound;

	FTimerHandle FireTimerHandle;
	FTimerHandle AltFireTimerHandle;

	UFUNCTION()
	void OnRep_Charging();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetFireStartLocation(FVector& StartTrace);

	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace);
};
