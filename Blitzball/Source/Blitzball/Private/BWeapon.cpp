// Fill out your copyright notice in the Description page of Project Settings.

#include "BWeapon.h"
#include "BCharacter.h"
#include "BPlayerController.h"
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
	ImpulseForce = 500000.0f;

	SetReplicates(true);
	bNetUseOwnerRelevancy = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ABWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABWeapon, BOwner, COND_None);
}

void ABWeapon::StartFire()
{
	Fire();
}

void ABWeapon::StopFire()
{

}

void ABWeapon::StartAltFire()
{

}

void ABWeapon::StopAltFire()
{

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

	ApplyImpulse(Impact, ShootDir);
}

void ABWeapon::AltFire()
{

}

void ABWeapon::ServerStartFire_Implementation()
{

}

bool ABWeapon::ServerStartFire_Validate()
{
	return true;
}

void ABWeapon::ServerStopFire_Implementation()
{

}

bool ABWeapon::ServerStopFire_Validate()
{
	return true;
}

void ABWeapon::ApplyImpulse(const FHitResult& Hit, const FVector& ShootDir)
{
	AActor* HitActor = Hit.GetActor();
	UPrimitiveComponent* HitComponent = Hit.GetComponent();
	if (HitActor != nullptr && (HitActor != this) && (HitComponent != nullptr) && HitComponent->IsSimulatingPhysics())
	{
		HitComponent->AddImpulseAtLocation(ShootDir * ImpulseForce, Hit.Location);
	}
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
