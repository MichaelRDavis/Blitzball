// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BCharacterMovement.generated.h"

UENUM(BlueprintType)
enum class EGait : uint8
{
	EWalking UMETA(DisplayName = "Walking"),
	ERunning UMETA(DisplayName = "Running"),
	ESprinting UMETA(DisplayName = "Sprinting")
};

UCLASS()
class BLITZBALL_API UBCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UBCharacterMovement();

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Movement")
	EGait CharacterGait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Running")
	float RunningAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Running")
	float RunningGroundFriction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintCooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintDuration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sprint")
	bool bIsSprinting;

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
};

class FSavedMove_BCharacter : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;

	bool bSavedIsSprinting;

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
