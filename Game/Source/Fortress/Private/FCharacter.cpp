// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacter.h"
#include "FCharacterMovement.h"
#include "FUsable.h"
#include "FInventoryItem.h"
#include "FWeapon.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#define COLLISION_USABLE ECC_GameTraceChannel1

AFCharacter::AFCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UFCharacterMovement>(ACharacter::CharacterMovementComponentName))
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

	FCharacterMovement = Cast<UFCharacterMovement>(GetCharacterMovement());

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bReceivesDecals = false;

	Health = 0;
	MaxHealth = 100;
	Shield = 50;
	MaxShield = 100;
	UseDistance = 400.0f;
	bIsUsableInFocus = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AFCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AFCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateInventory();

	if (Health == 0)
	{
		Health = MaxHealth;
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

void AFCharacter::EquipWeapon(AFWeapon* Weap)
{
	if (Weap)
	{
		Weapon = Weap;
		Weapon->OnEquip();
	}
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

FHitResult AFCharacter::RayTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(RayTrace), true, Instigator);

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_GameTraceChannel3, TraceParams);

	return Hit;
}

