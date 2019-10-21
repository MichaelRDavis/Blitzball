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
