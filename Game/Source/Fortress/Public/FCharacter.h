// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FCharacter.generated.h"

class UCameraComponent;

UCLASS()
class FORTRESS_API AFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	/** Character mesh: 1st person view(arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Pawn)
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* FirstPersonCameraComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Handles moving forward/backward */
	virtual void MoveForward(float Value);

	/** Handles strafing movement left/right */
	virtual void MoveRight(float Value);

	/** Called when we die */
	UFUNCTION(BlueprintCallable, Category = Pawn, meta = (DisplayName = Die))
	bool K2_Die(AController* EventInstigator, TSubclassOf<UDamageType> DamageType);
	virtual bool Die(AController* EvnetInstigator, const FDamageEvent& DamageEvent, AActor* DamageCauser = nullptr);

	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Death();

protected:
	/** Identifies if player is in its dying state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)
	bool bIsDead;

	/** Current health of the player */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	int32 Health;

	/** Max health of the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	int32 MaxHealth;

	/** Current shield amount */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	int32 Shield;

	/** Max shield amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	int32 MaxShield;

	/** Sound played on jump */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* JumpSound;

	/** Sound played on death */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* DeathSound;

	/** Sound played on hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* HitSound;
};
