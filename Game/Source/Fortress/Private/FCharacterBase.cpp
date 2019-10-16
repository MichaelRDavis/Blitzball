// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacterBase.h"
#include "Net/UnrealNetwork.h"

AFCharacterBase::AFCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFCharacterBase, Health, COND_None);
	DOREPLIFETIME_CONDITION(AFCharacterBase, Shield, COND_None);
}

void AFCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AFCharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return 0.0f;
	}

	int32 ResultDamage = FMath::TruncToInt(Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser));
	if (ResultDamage > 0)
	{
		Health -= ResultDamage;
		if (Health <= 0)
		{
			Die(EventInstigator, DamageEvent, DamageCauser);
		}
		else
		{

		}
	}

	return (float)ResultDamage;
}

bool AFCharacterBase::K2_Die(AController* EventInstigator, TSubclassOf<UDamageType> DamageType)
{
	return Die(EventInstigator, FPointDamageEvent(Health + 1, FHitResult(), FVector(0.0f, 0.0f, -1.0f), DamageType));
}

bool AFCharacterBase::Die(AController* EvnetInstigator, const FDamageEvent& DamageEvent, AActor* DamageCauser /*= nullptr*/)
{
	if (bIsDead)
	{
		return false;
	}

	Health = FMath::Min<int32>(0.0f, Health);

	Death();
	return true;
}

void AFCharacterBase::Death()
{
	if (bIsDead)
	{
		return;
	}

	bIsDead = true;
}

void AFCharacterBase::StartRagdoll()
{

}

int32 AFCharacterBase::GetHealth() const
{
	return Health;
}

int32 AFCharacterBase::GetMaxHealth() const
{
	return MaxHealth;
}

bool AFCharacterBase::IsDead() const
{
	return Health < 0 || bIsDead;
}

