// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BCharacter.generated.h"

class UCameraComponent;
class ABWeapon;
class ABBlitzball;
class UBCharacterMovement;

/** Replicated information on a hit we've taken */
USTRUCT(BlueprintType)
struct FTakeHitInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = TakeHitInfo)
	int32 Damage;
};

UCLASS(Abstract, config=Game)
class BLITZBALL_API ABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABCharacter(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;
	virtual void PawnClientRestart() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	/** Pawn mesh: 1st person (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/**  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UBCharacterMovement* BCharacterMovement;

public:
	/** Handles moving forward */
	void MoveForward(float Value);

	/** Handles strafing movement left and right */
	void MoveRight(float Value);

	virtual bool CanJumpInternal_Implementation() const;

	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StartSpeedBoost();
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StopSpeedBoost();

	/** Update team outline colors for player mesh */
	void UpdateTeamColors();

	/** Get current player health */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	int32 GetHealth() const;

	/** Get max player health */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	int32 GetMaxHealth() const;

	/** Starts weapon fire */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StartFire();

	/** Stops weapon fire */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StopFire();

	/** Starts weapon alt fire */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StartAltFire();

	/** Stops weapon alt fire */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StopAltFire();

	/** Check if player can fire weapon */
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

	/** Equip weapon */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEquipWeapon(ABWeapon* Weap);
	void ServerEquipWeapon_Implementation(ABWeapon* Weap);
	bool ServerEquipWeapon_Validate(ABWeapon* Weap);

	/** Perform quick melee attack */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void QuickMelee();

protected:
	/** Current health of the player */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	int32 Health;

	/** Max health of the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	int32 MaxHealth;

	/** Weapon class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	TSubclassOf<ABWeapon> WeaponClass;

	/** Current weapon */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	ABWeapon* Weapon;

	/** Max distance of melee trace */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float MeleeTraceDistance;
	
	/** Impulse velocity applied on melee hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float MeleeForce;

	/** Damage applied on melee hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	int32 MeleeDamage;

	/** Cooldown time for quick melee attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float MeleeCooldownTime;

	/**  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Pawn)
	ABBlitzball* BlitzballInView;

	/**  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn)
	bool bIsBlitzballInView;

	/**  */
	UFUNCTION(BlueprintCallable, Category=Pawn)
	ABBlitzball* GetBlitzballInView();

	FTimerHandle QuickMeleeTimer;

	/** Perform a ray trace */
	FHitResult RayTrace(const FVector& StartTrace, const FVector& EndTrace) const;

public:
	/** Returns FirstPersonMesh subobject */
	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
	/** Returns FirstPersonCameraComponent subobject */
	FORCEINLINE UCameraComponent* GetCharacterCameraComponent() const { return FirstPersonCameraComponent; }
};
