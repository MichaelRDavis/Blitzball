// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FCharacterBase.generated.h"

USTRUCT(BlueprintType)
struct FTakeHitInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 Damage;
	UPROPERTY()
	uint8 Count;
};

UCLASS(Abstract)
class FORTRESS_API AFCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AFCharacterBase(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Called when we die */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Pawn, meta = (DisplayName = Die))
	bool K2_Die(AController* EventInstigator, TSubclassOf<UDamageType> DamageType);
	virtual bool Die(AController* EvnetInstigator, const FDamageEvent& DamageEvent, AActor* DamageCauser = nullptr);

	virtual void SetTakeHitInfo(int32 Damage);

	/** Modify damage taken by this pawn */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void ModifyDamageTaken(int32& Damage);

	/** Called on pawn death, notifies server and client of death */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	virtual void Death();

	/**  */
	virtual void PlayTakeHitEffects();

	/**  */
	virtual void NotifyTakeHit(AController* InstigatedBy, int32 Damage, const FDamageEvent& DamageEvent);

	/** Switch to ragdoll on death */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StartRagdoll();

	/** Get the current health of the pawn */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	int32 GetHealth() const;

	/** Get the max health of the pawn */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	int32 GetMaxHealth() const;

	/** Check if pawn is dead */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	bool IsDead() const;

	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	UPROPERTY(Transient, ReplicatedUsing = OnRep_LastTakeHitInfo)
	FTakeHitInfo LastTakeHitInfo;

	/** Identifies if pawn is in its dying state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)
	bool bIsDead;

	/** True if currently in ragdoll state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)
	bool bInRagdoll;

	/** Death cleanup time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float DeathCleanupTime;

	/** Current health of the pawn */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	int32 Health;

	/** Max health of the pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	int32 MaxHealth;

	/** Current shield amount */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Pawn)
	int32 Shield;

	/** Max shield amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	int32 MaxShield;

	/** Sound played on death */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* DeathSound;

	/** Sound played on hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	USoundBase* HitSound;
};
