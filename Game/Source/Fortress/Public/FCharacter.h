// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FCharacterBase.h"
#include "FCharacter.generated.h"

class UCameraComponent;
class UFCharacterMovement;
class AFInventoryItem;
class AFWeapon;

UCLASS(config=Game)
class FORTRESS_API AFCharacter : public AFCharacterBase
{
	GENERATED_BODY()

public:
	AFCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Pawn)
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	UFCharacterMovement* FCharacterMovement;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Handles moving forward/backward */
	virtual void MoveForward(float Value);

	/** Handles strafing movement left/right */
	virtual void MoveRight(float Value);

protected:
	/** Items in inventory */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	TArray<AFInventoryItem*> Inventory;

	/** Currently equipped weapon */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	AFWeapon* Weapon;
	UPROPERTY(BlueprintReadOnly, Category = Pawn)
	AFWeapon* SecondaryWeapon;

	/** Sound played on jump */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* JumpSound;
};
