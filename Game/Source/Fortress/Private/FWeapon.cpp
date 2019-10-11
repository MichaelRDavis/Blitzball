// Fill out your copyright notice in the Description page of Project Settings.

#include "FWeapon.h"
#include "Net/UnrealNetwork.h"

AFWeapon::AFWeapon()
{

}

void AFWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AFWeapon::StartFire()
{

}

void AFWeapon::StopFire()
{

}

void AFWeapon::AttachToOwner()
{

}

void AFWeapon::DetachFromOwner()
{

}
