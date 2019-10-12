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
};
