// Fill out your copyright notice in the Description page of Project Settings.

#include "BGoal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ABGoal::ABGoal()
{
	GoalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalBoxCollision"));
	GoalBox->SetupAttachment(GetRootComponent());

	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	GoalMesh->SetupAttachment(GoalBox);

	SaveBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveBoxCollision"));
	SaveBox->SetupAttachment(GoalBox);
}

