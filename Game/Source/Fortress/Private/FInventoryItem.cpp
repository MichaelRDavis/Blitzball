// Fill out your copyright notice in the Description page of Project Settings.

#include "FInventoryItem.h"
#include "FCharacter.h"

AFInventoryItem::AFInventoryItem()
{
	SetReplicates(true);
	bOnlyRelevantToOwner = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AFInventoryItem::GivenTo(AFCharacter* NewOwner)
{
	Instigator = NewOwner;
	SetOwner(NewOwner);
	FOwner = NewOwner;
}

void AFInventoryItem::Removed()
{
	Instigator = nullptr;
	SetOwner(nullptr);
	FOwner = nullptr;
}

bool AFInventoryItem::CanItemStack()
{
	return ItemData.bIsStackable;
}

void AFInventoryItem::CheckForStack()
{
	bool bStackSize = ItemData.StackCount < ItemData.MaxStackCount;
	bool bItemName = ItemData.Name.EqualTo(ItemData.Name);
	bool bIsStacked = false;
	if (bStackSize && bItemName)
	{
		bIsStacked = true;
		if (bIsStacked)
		{
			ItemData.StackCount++;
		}
	}
}
