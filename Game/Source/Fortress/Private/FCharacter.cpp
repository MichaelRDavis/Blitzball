// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

AFCharacter::AFCharacter()
{
	// Create a CameraCompoent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0.0f, 0.0f, BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->bReceivesDecals = false;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bReceivesDecals = false;

	Health = 0;
	MaxHealth = 100;
	Shield = 0;
	MaxShield = 100;
	PrimaryActorTick.bCanEverTick = true;
}

void AFCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFCharacter, Health, COND_None);
	DOREPLIFETIME_CONDITION(AFCharacter, Shield, COND_None);
}

void AFCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Health == 0)
	{
		Health = MaxHealth;
	}
}

void AFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AFCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AFCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in forward direction
		const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// FInd out which way is right
		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in right direction
		const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

bool AFCharacter::K2_Die(AController* EventInstigator, TSubclassOf<UDamageType> DamageType)
{
	return Die(EventInstigator, FPointDamageEvent(Health + 1, FHitResult(), FVector(0.0f, 0.0f, -1.0f), DamageType));
}

bool AFCharacter::Die(AController* EvnetInstigator, const FDamageEvent& DamageEvent, AActor* DamageCauser /*= nullptr*/)
{
	if (bIsDead)
	{
		return false;
	}

	Health = FMath::Min<int32>(0.0f, Health);

	Death();
	return true;
}

void AFCharacter::Death()
{
	if (bIsDead)
	{
		return;
	}

	bIsDead = false;
}
