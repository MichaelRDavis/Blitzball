// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacter.h"
#include "BWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

ABCharacter::ABCharacter()
{
	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0.0f, 0.0f, BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetCollisionObjectType(ECC_Pawn);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->bReceivesDecals = false;

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->bReceivesDecals = false;

	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABCharacter, Weapon, COND_None);
}

void ABCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	UpdateTeamColors();
}

void ABCharacter::Destroyed()
{
	Super::Destroyed();

	DestroyWeapon();
}

void ABCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in forward direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}

void ABCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in right direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}

void ABCharacter::UpdateTeamColors()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(253);
}

void ABCharacter::StartFire()
{
	if (Weapon)
	{
		Weapon->StartFire();
	}
}

void ABCharacter::StopFire()
{
	if (Weapon)
	{
		Weapon->StopFire();
	}
}

bool ABCharacter::CanFire() const
{
	return true;
}

void ABCharacter::SpawnWeapon()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABWeapon* Weap = GetWorld()->SpawnActor<ABWeapon>(WeaponClass, SpawnInfo);
	if (Weap)
	{
		EquipWeapon(Weap);
	}
}

void ABCharacter::DestroyWeapon()
{
	if (Weapon != nullptr)
	{
		Weapon->Remove();
		Weapon->UnEquip();
		Weapon->Destroy();
	}
}

void ABCharacter::EquipWeapon(ABWeapon* Weap)
{
	if (Weap)
	{
		Weap->GiveTo(this);
		Weap->Equip();
	}
}

