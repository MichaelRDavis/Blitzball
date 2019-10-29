// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "FCharacterBase.h"
#include "FCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;
class UFCharacterMovement;
class AFInventoryItem;
class AFWeapon;
class AFUsable;

UCLASS(config=Game)
class FORTRESS_API AFCharacter : public AFCharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AFCharacter(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}

	/** Camera boom */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Pawn)
	USpringArmComponent* CameraBoom;

	/** Third person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* CharacterCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	UFCharacterMovement* FCharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	UAbilitySystemComponent* AbilitySystem;

protected:
	virtual void BeginPlay() override;

	AFUsable* GetUsableInView();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float UseDistance;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn)
	bool bIsUsableInFocus;
	UPROPERTY(BlueprintReadOnly, Category = Pawn)
	AFUsable* UsableInFocus;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void CreateInventory();

	/** Add item to inventory */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Pawn)
	virtual void AddItem(AFInventoryItem* Item);

	/** Remove item from inventory */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Pawn)
	virtual void RemoveItem(AFInventoryItem* Item);

	/** Find item in inventory */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual AFInventoryItem* FindItem(TSubclassOf<AFInventoryItem> ItemClass);

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void DropItem(AFInventoryItem* Item);

	/**  */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void DropInventory();

	/** Equips weapon from inventory */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void EquipWeapon(AFWeapon* Weap);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerEquipWeapon(AFWeapon* Weap);
	virtual void ServerEquipWeapon_Implementation(AFWeapon* Weap);
	virtual bool ServerEquipWeapon_Validate(AFWeapon* Weap);

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void SwitchWeapon(AFWeapon* NewWeapon, AFWeapon* LastWeapon);

	virtual bool CanJumpInternal_Implementation() const override;

	/** Handles moving forward/backward */
	virtual void MoveForward(float Value);

	/** Handles strafing movement left/right */
	virtual void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Sprint();
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void StopSprinting();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	virtual bool IsSprinting() const;

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void StartTargeting();
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void StopTargeting();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	virtual bool IsTargeting() const;

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Use();
	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerUse();
	virtual void ServerUse_Implementation();
	virtual bool ServerUse_Validate();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void StartFire();
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void NextWeapon();
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void PrevWeapon();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void EquipPrimaryWeapon();
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void EquipSecondaryWeapon();

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void OnMelee();

	/** Check if pawn can fire primary weapon */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	virtual bool CanFire() const;

	/** Check if pawn can reload primary weapon */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	virtual bool CanReload();

	/** Get current weapon */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	AFWeapon* GetWeapon() const;

	/** Characters default inventory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	TArray<TSubclassOf<AFInventoryItem>> DefaultInventoryClasses;

	/** Items in inventory */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	TArray<AFInventoryItem*> Inventory;

protected:
	/** Currently equipped weapon */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	AFWeapon* Weapon;

	/** Sound played on jump */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* JumpSound;

	/** Sound played on sprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* SprintSound;

	/** Sound played on melee */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* MeleeSound;

private:
	FHitResult RayTrace(const FVector& StartTrace, const FVector& EndTrace) const;
};
