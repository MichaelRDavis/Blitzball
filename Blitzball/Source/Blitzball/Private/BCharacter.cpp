// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacter.h"
#include "BWeapon.h"
#include "BPlayerState.h"
#include "BPlayerController.h"
#include "BCharacterMovement.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

#define COLLISION_MELEE ECC_GameTraceChannel2

ABCharacter::ABCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBCharacterMovement>(ACharacter::CharacterMovementComponentName))
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

	BCharacterMovement = Cast<UBCharacterMovement>(GetCharacterMovement());

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->bReceivesDecals = false;

	MeleeTraceDistance = 250.0f;
	MeleeForce = 10000.0f;
	MeleeDamage = 30;

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
}

void ABCharacter::Destroyed()
{
	Super::Destroyed();

	DestroyWeapon();
}

void ABCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	UpdateTeamColors();
}

void ABCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UpdateTeamColors();
}

void ABCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (GetPlayerState() != nullptr)
	{
		UpdateTeamColors();
	}
}

void ABCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(Rotation);

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
		const FRotator YawRotation(Rotation);

		// Add movement in right direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}

void ABCharacter::StartSpeedBoost()
{
	if (BCharacterMovement)
	{
		BCharacterMovement->SetSpeedBoost(true);
	}
}

void ABCharacter::StopSpeedBoost()
{
	if (BCharacterMovement)
	{
		BCharacterMovement->SetSpeedBoost(false);
	}
}

void ABCharacter::UpdateTeamColors()
{
	ABPlayerState* Player = Cast<ABPlayerState>(GetPlayerState());
	if (Player)
	{
		if (Player->GetTeamNumber() == 0)
		{
			GetMesh()->SetRenderCustomDepth(true);
			GetMesh()->SetCustomDepthStencilValue(253);
		}
		else if (Player->GetTeamNumber() == 1)
		{
			GetMesh()->SetRenderCustomDepth(true);
			GetMesh()->SetCustomDepthStencilValue(254);
		}
	}
}

int32 ABCharacter::GetHealth() const
{
	return Health;
}

int32 ABCharacter::GetMaxHealth() const
{
	return MaxHealth;
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

void ABCharacter::StartAltFire()
{
	if (Weapon)
	{
		Weapon->StartAltFire();
	}
}

void ABCharacter::StopAltFire()
{
	if (Weapon)
	{
		Weapon->StopAltFire();
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
		if (Role == ROLE_Authority)
		{
			Weapon = Weap;
			Weapon->GiveTo(this);
			Weapon->Equip();
		}
		else
		{
			ServerEquipWeapon(Weap);
		}
	}
}

void ABCharacter::ServerEquipWeapon_Implementation(ABWeapon* Weap)
{
	EquipWeapon(Weap);
}

bool ABCharacter::ServerEquipWeapon_Validate(ABWeapon* Weap)
{
	return true;
}

void ABCharacter::QuickMelee()
{
	ABPlayerController* PlayerController = Cast<ABPlayerController>(GetController());
	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;

		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
	}
}

FHitResult ABCharacter::RayTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(RayTrace), true, Instigator);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_MELEE, TraceParams);

	return Hit;
}

