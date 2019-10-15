// Fill out your copyright notice in the Description page of Project Settings.

#include "FLootCrate.h"
#include "FPickup.h"
#include "Components/StaticMeshComponent.h"

AFLootCrate::AFLootCrate()
{
	CrateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CrateMesh->SetupAttachment(GetRootComponent());
}

void AFLootCrate::SpawnLoot()
{
	if (DropType != nullptr && FMath::Rand() < DropChance)
	{
		
	}
}
