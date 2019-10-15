// Fill out your copyright notice in the Description page of Project Settings.

#include "FGrenade.h"
#include "FCharacter.h"
#include "FProj_Grenade.h"
#include "Engine/World.h"

AFGrenade::AFGrenade()
{
	Count = 0;
	MaxCount = 2;
}

void AFGrenade::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Count == 0)
	{
		Count = MaxCount;
	}
}

void AFGrenade::SpawnGrenade()
{
	const FRotator SpawnRotation = FOwner->GetControlRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(SpawnOffset);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor<AFProj_Grenade>(GrenadeClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}
