// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract, Blueprintable)
class FORTRESS_API AFProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFProjectile();

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FRadialDamageParams DamageParams;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	TSubclassOf<UDamageType> DamageType;

	/** Controller that fired projectile */
	UPROPERTY(BlueprintReadWrite, Category = Projectile)
	AController* InstigatorController;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Projectile)
	void ProcessHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector& HitLocation, const FVector& HitNormal);
	void ProcessHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector& HitLocation, const FVector& HitNormal);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Projectile)
	void ApplyDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector HitLocation, const FVector& HitNormal);
	void ApplyDamage_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector HitLocation, const FVector& HitNormal);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void InitVelocity(FVector& ShootDir);
};
