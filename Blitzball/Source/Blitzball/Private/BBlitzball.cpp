// Fill out your copyright notice in the Description page of Project Settings.

#include "BBlitzball.h"

ABBlitzball::ABBlitzball()
{
	SetReplicates(true);
	bReplicateMovement = true;
}

void ABBlitzball::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

