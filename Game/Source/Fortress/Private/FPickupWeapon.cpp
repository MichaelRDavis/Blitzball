// Fill out your copyright notice in the Description page of Project Settings.

#include "FPickupWeapon.h"
#include "FCharacter.h"
#include "FInventoryItem.h"
#include "FWeapon.h"

AFPickupWeapon::AFPickupWeapon()
{

}

void AFPickupWeapon::OnUsed_Implementation(AFCharacter* Character)
{
	if (Character)
	{
		// TODO: Need to check for a free weapon slot
		// TODO: If there are no free weapon slots allow the player to switch weapon
	}
}

void AFPickupWeapon::OnBeginFocus_Implementation()
{

}

void AFPickupWeapon::OnEndFocus_Implementation()
{

}
