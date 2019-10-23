// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FCharacterMovement.generated.h"

UCLASS()
class FORTRESS_API UFCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UFCharacterMovement();

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	/** Multiplier for sprint movement speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprint)
	float SprintSpeedMultiplier;

	/** Multiplier for sprint acceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprint, meta = (DisplayName = "Sprint Acceleration Multiplier"))
	float SprintAccelMultiplier;

	/**  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Sprint)
	bool bWantsToSprint;

	/**  */
	void SetSprinting(bool bNewSprinting);

	/** Multiplier for targeting movement speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	float TargetingSpeedMultiplier;

	/** Multiplier for targeting acceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting, meta = (DisplayName = "Targeting Acceleration Multiplier"))
	float TargetingAccelMultiplier;

	/**  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Targeting)
	bool bIsTargeting;

	/**  */
	void SetTargeting(bool bNewTargeting);

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Multijump)
	int32 MaxJumpCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Multijump)
	int32 CurrentJumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Multijump)
	float GravJumpImpulse;

	bool CanJump();

	virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;
	virtual bool DoJump(bool bReplayingMoves) override;
};

class FSavedMove_FCharacter : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;

	int32 SavedJumpCount;

	bool bSavedWantsToSprint;
	bool bSavedIsTargeting;

	virtual void Clear() override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	virtual uint8 GetCompressedFlags() const override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
	virtual bool IsImportantMove(const FSavedMovePtr& LastAckedMove) const override;
	virtual void PostUpdate(ACharacter* Character, EPostUpdateMode PostUpdateMode) override;
	virtual void PrepMoveFor(ACharacter* Character) override;
};

class FNetworkPredictionData_Client_FCharacter : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;

	FNetworkPredictionData_Client_FCharacter(const UCharacterMovementComponent& ClientMovement)
		: Super(ClientMovement)
	{

	}

	virtual FSavedMovePtr AllocateNewMove() override;
};
