// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BWeapon.generated.h"

class ABCharacter;

UCLASS()
class BLITZBALL_API ABWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABWeapon();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void FireInstantHit();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void ApplyImpulse(const FHitResult& Hit, const FVector& ShootDir);

	virtual void GiveTo(ABCharacter* NewOwner);
	virtual void Remove();

	virtual void Equip();
	virtual void UnEquip();

protected:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Weapon)
	ABCharacter* BOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FName HandsAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float ImpulseForce;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Weapon)
	FVector GetFireStartLocation(FVector& StartTrace);

	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace);
};
