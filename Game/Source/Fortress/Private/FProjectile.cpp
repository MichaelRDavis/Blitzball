// Fill out your copyright notice in the Description page of Project Settings.

#include "FProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFProjectile::AFProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->InitSphereRadius(0.0f);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFProjectile::OnOverlapBegin);
	CollisionComp->bTraceComplexOnMove = true;
	CollisionComp->bReceivesDecals = false;
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->SetUpdatedComponent(CollisionComp);
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = false;

	DamageParams.BaseDamage = 20;
	DamageParams.DamageFalloff = 1.0f;
	InitialLifeSpan = 3.0f;

	SetReplicates(true);
	bReplicateMovement = true;
	bNetTemporary = false;
	NetPriority = 2.0f;
	MinNetUpdateFrequency = 100.0f;
	PrimaryActorTick.bCanEverTick = true;
}

void AFProjectile::ProcessHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector& HitLocation, const FVector& HitNormal)
{

}

void AFProjectile::ApplyDamage_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector HitLocation, const FVector& HitNormal)
{

}

void AFProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult Hit;
	if (bFromSweep)
	{
		Hit = SweepResult;
	}

	ProcessHit(OtherActor, OtherComp, Hit.Location, Hit.Normal);
}

