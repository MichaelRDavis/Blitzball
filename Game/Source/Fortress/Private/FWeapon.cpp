// Fill out your copyright notice in the Description page of Project Settings.

#include "FWeapon.h"
#include "FCharacter.h"
#include "FPlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "DrawDebugHelpers.h"

#define COLLISION_WEAPON ECC_GameTraceChannel2

AFWeapon::AFWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->bReceivesDecals = false;
	Mesh->CastShadow = false;
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	Ammo = 0;
	MagazineSize = 0;
	MaxAmmo = 100;
	MaxMagazineSize = 20;
	InitialMagazines = 4;
	FireRate = 0.2f;
	Spread = 5.0f;
	MaxTracerRange = 10000.0f;

	SetReplicates(true);
	bNetUseOwnerRelevancy = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AFWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AFWeapon::OnEquip()
{
	AttachToOwner();
}

void AFWeapon::UnEquip()
{
	DetachFromOwner();
}

void AFWeapon::Fire()
{
	FireInstantHit();
}

void AFWeapon::StartFire()
{
	Fire();
}

void AFWeapon::StopFire()
{
	
}

void AFWeapon::ServerStartFire_Implementation()
{
	StartFire();
}

bool AFWeapon::ServerStartFire_Validate()
{
	return true;
}

void AFWeapon::ServerStopFire_Implementation()
{
	StopFire();
}

bool AFWeapon::ServerStopFire_Validate()
{
	return true;
}

void AFWeapon::FireInstantHit()
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float CurrentSpread = Spread;
	const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

	const FVector AimDir = GetAdjustedAim();
	const FVector StartTrace = GetFireStartLocation(AimDir);
	const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
	const FVector EndTrace = StartTrace + ShootDir * MaxTracerRange;

	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
}

void AFWeapon::FireProjectile()
{

}

void AFWeapon::AttachToOwner()
{
	if (FOwner)
	{
		Mesh->AttachToComponent(FOwner->FirstPersonMesh, FAttachmentTransformRules::KeepRelativeTransform, HandsAttachSocket);
		Mesh->SetHiddenInGame(false);
	}
}

void AFWeapon::DetachFromOwner()
{
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh->SetHiddenInGame(true);
}

FVector AFWeapon::GetAdjustedAim() const
{
	AFPlayerController* const PlayerController = Instigator ? Cast<AFPlayerController>(Instigator->Controller) : nullptr;
	FVector FinalAim = FVector::ZeroVector;
	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
		FinalAim = CamRot.Vector();
	}

	return FinalAim;
}

FVector AFWeapon::GetFireStartLocation(const FVector& AimDir) const
{
	AFPlayerController* PlayerController = FOwner ? Cast<AFPlayerController>(FOwner->GetController()) : nullptr;
	FVector OutStartTrace = FVector::ZeroVector;
	if (PlayerController)
	{
		FRotator UnusedRot;
		PlayerController->GetPlayerViewPoint(OutStartTrace, UnusedRot);

		OutStartTrace = OutStartTrace + AimDir * ((Instigator->GetActorLocation() - OutStartTrace) | AimDir);
	}

	return OutStartTrace;
}

FHitResult AFWeapon::WeaponTrace(const FVector& TraceFrom, const FVector TraceTo) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, COLLISION_WEAPON, TraceParams);
	DrawDebugLine(GetWorld(), TraceFrom, TraceTo, FColor::Red, false, 1, 0, 1);

	return Hit;
}
