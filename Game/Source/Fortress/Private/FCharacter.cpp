// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacter.h"
#include "FCharacterMovement.h"
#include "FUsable.h"
#include "FInventoryItem.h"
#include "FWeapon.h"
#include "AbilitySystemComponent.h"
#include "GameFramework//SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

#define COLLISION_USABLE ECC_GameTraceChannel1

AFCharacter::AFCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UFCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	// Create a CameraCompoent
	CharacterCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CharacterCameraComponent->SetupAttachment(GetCapsuleComponent());
	CharacterCameraComponent->RelativeLocation = FVector(0.0f, 0.0f, BaseEyeHeight);
	CharacterCameraComponent->bUsePawnControlRotation = true;

	// 
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetupAttachment(CharacterCameraComponent);
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->bReceivesDecals = false;

	FCharacterMovement = Cast<UFCharacterMovement>(GetCharacterMovement());

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetOwnerNoSee(true);

	Health = 0;
	MaxHealth = 100;
	Shield = 0;
	MaxShield = 100;
	UseDistance = 400.0f;
	bIsUsableInFocus = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AFCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFCharacter, Weapon, COND_None);

	DOREPLIFETIME_CONDITION(AFCharacter, Inventory, COND_OwnerOnly);
}

void AFCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateInventory();

	if (Health == 0 && Shield == 0)
	{
		Health = MaxHealth;
		Shield = MaxShield;
	}
}

AFUsable* AFCharacter::GetUsableInView()
{
	FVector CamLoc;
	FRotator CamRot;

	if (Controller == nullptr)
	{
		return nullptr;
	}

	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector StartTrace = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector EndTrace = StartTrace + (Direction * UseDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_USABLE, TraceParams);

	return Cast<AFUsable>(Hit.GetActor());
}

void AFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		AFUsable* Usable = GetUsableInView();
		if (UsableInFocus != Usable)
		{
			if (UsableInFocus)
			{
				UsableInFocus->OnEndFocus();
			}

			bIsUsableInFocus = false;
		}

		UsableInFocus = Usable;
		if (Usable)
		{
			if (!bIsUsableInFocus)
			{
				Usable->OnBeginFocus();
				bIsUsableInFocus = true;
			}
		}
	}
}

void AFCharacter::CreateInventory()
{
	for (int32 i = 0; i < DefaultInventoryClasses.Num(); i++)
	{
		if (DefaultInventoryClasses[i])
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AFInventoryItem* NewItem = GetWorld()->SpawnActor<AFInventoryItem>(DefaultInventoryClasses[i], SpawnInfo);
			AddItem(NewItem);
		}
	}

	if (Inventory.Num() > 0)
	{
		AFWeapon* Weap = Cast<AFWeapon>(FindItem(DefaultInventoryClasses[0]));
		if (Weap)
		{
			EquipWeapon(Weap);
		}
	}
}

void AFCharacter::AddItem(AFInventoryItem* Item)
{
	if (Item)
	{
		Item->GivenTo(this);
		Inventory.AddUnique(Item);
	}
}

void AFCharacter::RemoveItem(AFInventoryItem* Item)
{
	if (Item)
	{
		Item->Removed();
		Inventory.RemoveSingle(Item);
	}
}

AFInventoryItem* AFCharacter::FindItem(TSubclassOf<AFInventoryItem> ItemClass)
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] && Inventory[i]->IsA(ItemClass))
		{
			return Inventory[i];
		}
	}

	return nullptr;
}

void AFCharacter::DropItem(AFInventoryItem* Item)
{
	const FVector EyeLoc = GetActorLocation() + BaseEyeHeight;
	const FVector Dist = GetControlRotation().RotateVector(FVector(100.0f, 0.0f, 0.0f));
	const FVector SpawnLoc = EyeLoc + Dist;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	RemoveItem(Item);
}

void AFCharacter::DropInventory()
{

}

void AFCharacter::EquipWeapon(AFWeapon* Weap)
{
	if (Weap)
	{
		if (Role == ROLE_Authority)
		{
			SwitchWeapon(Weap, Weapon);
		}
		else
		{
			ServerEquipWeapon(Weap);
		}
	}
}

void AFCharacter::ServerEquipWeapon_Implementation(AFWeapon* Weap)
{
	EquipWeapon(Weap);
}

bool AFCharacter::ServerEquipWeapon_Validate(AFWeapon* Weap)
{
	return true;
}

void AFCharacter::SwitchWeapon(AFWeapon* NewWeapon, AFWeapon* LastWeapon)
{
	AFWeapon* LocalLastWeapon = nullptr;

	if (LastWeapon != nullptr)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != Weapon)
	{
		LocalLastWeapon = Weapon;
	}

	if (LocalLastWeapon)
	{
		LocalLastWeapon->UnEquip();
	}

	Weapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->GivenTo(this);
		NewWeapon->OnEquip();
	}
}

bool AFCharacter::CanJumpInternal_Implementation() const
{
	bool bCanJump = Super::CanJumpInternal_Implementation();
	if (FCharacterMovement)
	{
		bCanJump = FCharacterMovement->CanJump();
	}

	return bCanJump;
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

void AFCharacter::Sprint()
{
	if (FCharacterMovement)
	{
		FCharacterMovement->SetSprinting(true);
	}
}

void AFCharacter::StopSprinting()
{
	if (FCharacterMovement)
	{
		FCharacterMovement->SetSprinting(false);
	}
}

bool AFCharacter::IsSprinting() const
{
	if (FCharacterMovement)
	{
		return FCharacterMovement->bWantsToSprint;
	}

	return false;
}

void AFCharacter::StartTargeting()
{
	if (FCharacterMovement && Weapon != nullptr)
	{
		FCharacterMovement->SetTargeting(true);
	}
}

void AFCharacter::StopTargeting()
{
	if (FCharacterMovement)
	{
		FCharacterMovement->SetTargeting(false);
	}
}

bool AFCharacter::IsTargeting() const
{
	if (FCharacterMovement)
	{
		return FCharacterMovement->bIsTargeting;
	}

	return false;
}

void AFCharacter::Use()
{
	ServerUse();
}

void AFCharacter::ServerUse_Implementation()
{
	AFUsable* Usable = GetUsableInView();
	if (Usable)
	{
		Usable->OnUsed(this);
	}
}

bool AFCharacter::ServerUse_Validate()
{
	return true;
}

void AFCharacter::StartFire()
{
	if (Weapon)
	{
		Weapon->StartFire();
	}
}

void AFCharacter::StopFire()
{
	if (Weapon)
	{
		Weapon->StopFire();
	}
}

void AFCharacter::Reload()
{
	if (Weapon)
	{
		Weapon->StartReload();
	}
}

void AFCharacter::NextWeapon()
{
	if (Inventory.Num() >= 2 && (Weapon == nullptr || Weapon->CurrentState != EWeaponState::EEquiping))
	{
		const int32 WeaponIndex = Inventory.IndexOfByKey(Weapon);
		AFWeapon* NexWeapon = Cast<AFWeapon>(Inventory[(WeaponIndex + 1) % Inventory.Num()]);
		EquipWeapon(NexWeapon);
	}
}

void AFCharacter::PrevWeapon()
{
	if (Inventory.Num() >= 2 && (Weapon == nullptr || Weapon->CurrentState != EWeaponState::EEquiping))
	{
		const int32 WeaponIndex = Inventory.IndexOfByKey(Weapon);
		AFWeapon* PrevWeapon = Cast<AFWeapon>(Inventory[(WeaponIndex - 1 + Inventory.Num()) % Inventory.Num()]);
		EquipWeapon(PrevWeapon);
	}
}

void AFCharacter::EquipPrimaryWeapon()
{
	if (Inventory.Num() >= 1)
	{
		AFWeapon* Weap = Cast<AFWeapon>(Inventory[0]);
		EquipWeapon(Weap);
	}
}

void AFCharacter::EquipSecondaryWeapon()
{
	if (Inventory.Num() >= 2)
	{
		AFWeapon* Weap = Cast<AFWeapon>(Inventory[1]);
		EquipWeapon(Weap);
	}
}

void AFCharacter::OnMelee()
{

}

bool AFCharacter::CanFire() const
{
	return !IsDead();
}

bool AFCharacter::CanReload()
{
	return !IsDead();
}

AFWeapon* AFCharacter::GetWeapon() const
{
	return Weapon;
}

FHitResult AFCharacter::RayTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(RayTrace), true, Instigator);

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_GameTraceChannel3, TraceParams);

	return Hit;
}

