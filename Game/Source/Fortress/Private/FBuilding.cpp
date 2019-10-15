// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuilding.h"
#include "Components/StaticMeshComponent.h"

AFBuilding::AFBuilding()
{
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BuildingMesh->SetupAttachment(RootComponent);

	Health = 0;
	MaxHealth = 250;
	GridSize = 100.0f;
	PrimaryActorTick.bCanEverTick = true;
}

void AFBuilding::BeginPlay()
{
	Super::BeginPlay();

	if (Health == 0)
	{
		Health = MaxHealth;
	}
}

void AFBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AFBuilding::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0)
	{
		return 0.0f;
	}

	int32 ResultDamage = FMath::TruncToInt(DamageAmount);
	if (ResultDamage > 0)
	{
		Health -= ResultDamage;
		if (Health <= 0)
		{
			Destroy();
		}
		else
		{

		}
	}

	return (float)DamageAmount;
}

