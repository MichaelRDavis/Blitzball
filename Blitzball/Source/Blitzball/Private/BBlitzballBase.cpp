// Fill out your copyright notice in the Description page of Project Settings.

#include "BBlitzballBase.h"
#include "BBlitzball.h"

ABBlitzballBase::ABBlitzballBase()
{

}

void ABBlitzballBase::BeginPlay()
{
	Super::BeginPlay();

	ServerSpawnBlitzball();
}

void ABBlitzballBase::ServerSpawnBlitzball_Implementation()
{
	Blitzball = GetWorld()->SpawnActor<ABBlitzball>(BlitzballClass, GetActorTransform());
	if (Blitzball)
	{
		Blitzball->HomeBase = this;
	}
}

bool ABBlitzballBase::ServerSpawnBlitzball_Validate()
{
	return true;
}

