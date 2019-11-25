// Fill out your copyright notice in the Description page of Project Settings.

#include "BGoal.h"
#include "BBlitzball.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ABGoal::ABGoal()
{
	GoalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalBoxCollision"));
	GoalBox->SetupAttachment(GetRootComponent());
	GoalBox->OnComponentBeginOverlap.AddDynamic(this, &ABGoal::OnOverlapBegin);

	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	GoalMesh->SetupAttachment(GoalBox);

	SaveBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveBoxCollision"));
	SaveBox->SetupAttachment(GoalBox);
}

void ABGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABBlitzball* Ball = Cast<ABBlitzball>(OtherActor);
		if (Ball)
		{
			Ball->Score();
			Ball->TeleportHome();
		}
	}
}

