// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BCharacter.generated.h"

class UCameraComponent;
class ABWeapon;

UCLASS()
class BLITZBALL_API ABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

private:
	/** Pawn mesh: 1st person (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	/** Handles moving forward */
	void MoveForward(float Value);

	/** Handles strafing movement left and right */
	void MoveRight(float Value);

	/** Update team outline colors for player mesh */
	void UpdateTeamColors();

	/** Starts weapon fire */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StartFire();

	/** Stops weapon fire */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StopFire();

	/** Check if pawn can fire weapon */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	bool CanFire() const;

	/** Spawns weapon class */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void SpawnWeapon();

	/** Removes weapon and destroys it */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void DestroyWeapon();

	/** Equips weapon from weapon class */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void EquipWeapon(ABWeapon* Weap);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	TSubclassOf<ABWeapon> WeaponClass;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	ABWeapon* Weapon;

public:
	/** Returns FirstPersonMesh subobject */
	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
	/** Returns FirstPersonCameraComponent subobject */
	FORCEINLINE UCameraComponent* GetCharacterCameraComponent() const { return FirstPersonCameraComponent; }
};
