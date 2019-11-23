// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BCharacterMovement.generated.h"

UCLASS()
class BLITZBALL_API UBCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UBCharacterMovement();

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Boost")
	float SpeedBoostMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Boost")
	float SpeedBoostAccelMultiplier;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Speed Boost")
	bool bWantsToSpeedBoost; 

	void SetSpeedBoost(bool bNewSpeedBoost);

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multijump", meta = (DisplayName = "Max Multijump Count"))
	int32 MaxMultiJumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multijump", meta = (DisplayName = "Current Multijump Count"))
	int32 CurrentMultiJumpCount;
};

class FSavedMove_BCharacter : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;

	bool bSavedWantsToSpeedBoost;

	virtual void Clear() override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	virtual uint8 GetCompressedFlags() const override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
	virtual bool IsImportantMove(const FSavedMovePtr& LastAckedMove) const override;
	virtual void PostUpdate(ACharacter* Character, EPostUpdateMode PostUpdateMode) override;
	virtual void PrepMoveFor(ACharacter* Character) override;
};

class FNetworkPredictionData_Client_BCharacter : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;

	FNetworkPredictionData_Client_BCharacter(const UCharacterMovementComponent& ClientMovement)
		: FNetworkPredictionData_Client_Character(ClientMovement)
	{

	}

	virtual FSavedMovePtr AllocateNewMove() override;
};
