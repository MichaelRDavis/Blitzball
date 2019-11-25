// Fill out your copyright notice in the Description page of Project Settings.

#include "BBlitzballBase.h"
#include "BBlitzball.h"

ABBlitzballBase::ABBlitzballBase()
{

}

void ABBlitzballBase::BeginPlay()
{
	Super::BeginPlay();

	Blitzball = GetWorld()->SpawnActor<ABBlitzball>(BlitzballClass, GetActorTransform());
}

