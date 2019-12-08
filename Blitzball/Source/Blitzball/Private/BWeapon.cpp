// Fill out your copyright notice in the Description page of Project Settings.

#include "BWeapon.h"
#include "BCharacter.h"
#include "BPlayerController.h"
#include "BBlitzball.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

#define COLLISION_WEAPON ECC_GameTraceChannel1

ABWeapon::ABWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->bSelfShadowOnly = true;

	TraceDistance = 1000.0f;
	BlitzballImpulseForce = 600000.0f;
	PlayerImpulseForce = 1000000.0f;
	bWantsToFire = false;
	bWantsToAltFire = false;
	FireCooldownTime = 1.0f;
	AltFireCooldownTime = 10.0f;
	ChargePercentage = 0.0f;
	ChargeAmount = 1.25f;
	bIsCharging = false;
	bIsCharged = false;

	SetReplicates(true);
	bNetUseOwnerRelevancy = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ABWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bWantsToFire)
	{
		bIsCharging = true;
	}

	if (bIsCharging)
	{
		ChargePercentage = FMath::Min(1.0f, ChargePercentage + ChargeAmount * DeltaSeconds);
		bIsCharged = (ChargePercentage >= 1.0f);
		if (bIsCharged)
		{
			BlitzballImpulseForce *= ChargePercentage;
		}
	}
}

void ABWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABWeapon, BOwner, COND_None);
}

void ABWeapon::StartFire()
{
	if (Role < ROLE_Authority)
	{
		ServerStartFire();
	}

	if (!bWantsToFire)
	{
		bWantsToFire = true;
		Fire();
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ABWeapon::SetCanFire, FireCooldownTime, false);
	}
}

void ABWeapon::StopFire()
{
	if (Role < ROLE_Authority)
	{
		ServerStopFire();
	}
}

void ABWeapon::StartAltFire()
{
	if (Role < ROLE_Authority)
	{
		ServerStartAltFire();
	}

	if (!bWantsToAltFire)
	{
		bWantsToAltFire = true;
		AltFire();
		GetWorldTimerManager().SetTimer(AltFireTimerHandle, this, &ABWeapon::SetCanAltFire, AltFireCooldownTime, false);
	}
}

void ABWeapon::StopAltFire()
{
	if (Role < ROLE_Authority)
	{
		ServerStopAltFire();
	}
}

void ABWeapon::Fire()
{
	FVector StartTrace;
	FVector ShootDir = GetFireStartLocation(StartTrace);

	// Adjust trace so there is nothing blocking the ray between the camera and the pawn, and calculate the distance from adjusted start
	StartTrace = StartTrace + ShootDir * ((BOwner->GetActorLocation() - StartTrace) | ShootDir);

	// Calculate endpoint of trace
	const FVector EndTrace = StartTrace + ShootDir * TraceDistance;

	// Check for impact
	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);

	// Apply impulse to Blitzball
	AActor* HitActor = Impact.GetActor();
	UPrimitiveComponent* HitComponent = Impact.GetComponent();
	if (HitActor != nullptr && (HitActor != this) && (HitComponent != nullptr) && HitComponent->IsSimulatingPhysics())
	{
		HitComponent->AddImpulseAtLocation(ShootDir * BlitzballImpulseForce, Impact.Location);

		ABBlitzball* Ball = Cast<ABBlitzball>(HitActor);
		if (Ball)
		{
			Ball->SetLastPlayer(BOwner);
		}
	}
}

void ABWeapon::AltFire()
{
	TArray<FHitResult> Hits;

	FVector StartLocation = BOwner->GetActorLocation();
	FVector StartTrace = StartLocation;
	FVector EndTrace = StartLocation;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(1000.0f);
	DrawDebugSphere(GetWorld(), BOwner->GetActorLocation(), 1000.0f, 50, FColor::Green);

	bool bHit = GetWorld()->SweepMultiByChannel(Hits, StartTrace, EndTrace, FQuat::Identity, ECC_PhysicsBody, Sphere);
	if (bHit)
	{
		for (FHitResult& Hit : Hits)
		{
			AActor* HitActor = Hit.GetActor();
			UPrimitiveComponent* HitComponent = Hit.GetComponent();
			if (HitActor != nullptr && (HitActor != this) && (HitComponent != nullptr) && HitComponent->IsSimulatingPhysics())
			{
				HitComponent->AddRadialImpulse(StartLocation, 1000.0f, PlayerImpulseForce, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
}

void ABWeapon::ServerStartFire_Implementation()
{
	StartFire();
}

bool ABWeapon::ServerStartFire_Validate()
{
	return true;
}

void ABWeapon::ServerStopFire_Implementation()
{
	StopFire();
}

bool ABWeapon::ServerStopFire_Validate()
{
	return true;
}

void ABWeapon::ServerStartAltFire_Implementation()
{
	StartAltFire();
}

bool ABWeapon::ServerStartAltFire_Validate()
{
	return true;
}

void ABWeapon::ServerStopAltFire_Implementation()
{
	StopAltFire();
}

bool ABWeapon::ServerStopAltFire_Validate()
{
	return true;
}

void ABWeapon::GiveTo(ABCharacter* NewOwner)
{
	if (BOwner != NewOwner)
	{
		BOwner = NewOwner;
		Instigator = NewOwner;
		SetOwner(NewOwner);
	}
}

void ABWeapon::Remove()
{
	BOwner = nullptr;
	Instigator = nullptr;
	SetOwner(nullptr);
}

void ABWeapon::Equip()
{
	if (BOwner)
	{
		Mesh->AttachToComponent(BOwner->GetFirstPersonMesh(), FAttachmentTransformRules::KeepRelativeTransform, HandsAttachSocket);
	}
}

void ABWeapon::UnEquip()
{
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}

void ABWeapon::SetCanFire()
{
	bWantsToFire = false;
}

void ABWeapon::SetCanAltFire()
{
	bWantsToAltFire = false;
}

FVector ABWeapon::GetFireStartLocation(FVector& StartTrace)
{
	FVector ShootDir;
	ABPlayerController* PlayerController = Cast<ABPlayerController>(BOwner->GetController());
	if (PlayerController)
	{
		// Calculate direction of fire and the start location for trace
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(StartTrace, CamRot);
		ShootDir = CamRot.Vector();
	}

	return ShootDir;
}

FHitResult ABWeapon::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace)
{
	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_WEAPON, TraceParams);
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1.0f, 0, 5.0f);

	return Hit;
}
