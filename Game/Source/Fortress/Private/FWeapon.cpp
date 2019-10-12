// Fill out your copyright notice in the Description page of Project Settings.

#include "FWeapon.h"
#include "FCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

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

void AFWeapon::StartFire()
{

}

void AFWeapon::StopFire()
{

}

void AFWeapon::FireInstantHit()
{

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
