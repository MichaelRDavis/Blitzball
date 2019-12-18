// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacterMovement.h"
#include "GameFramework/Character.h"

UBCharacterMovement::UBCharacterMovement()
{
	MaxWalkSpeed = 1200.0f;
	AirControl = 0.555f;
	MaxAcceleration = 3200.0f;
	GroundFriction = 10.5f;
	BrakingFriction = 5.0f;
	GravityScale = 1.0f;
	JumpZVelocity = 700.0f;
	SpeedBoostMultiplier = 1.5f;
	SpeedBoostAccelMultiplier = 1.5f;
	bWantsToSpeedBoost = false;
	MaxMultiJumpCount = 1;
	CurrentMultiJumpCount = 0;
	MultiJumpImpulse = 900.0f;
	NavAgentProps.bCanCrouch = true;
	NetworkSmoothingMode = ENetworkSmoothingMode::Exponential;
}

void UBCharacterMovement::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	//bWantsToSpeedBoost = (Flags & FSavedMove_BCharacter::FLAG_Custom_0) != 0;
}

FNetworkPredictionData_Client* UBCharacterMovement::GetPredictionData_Client() const
{
	if (!ClientPredictionData)
	{
		UBCharacterMovement* MutableThis = const_cast<UBCharacterMovement*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Character(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.0f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.0f;
	}

	return ClientPredictionData;
}

void UBCharacterMovement::SetSpeedBoost(bool bNewSpeedBoost)
{
	bWantsToSpeedBoost = bNewSpeedBoost;
}

float UBCharacterMovement::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	if (bWantsToSpeedBoost)
	{
		MaxSpeed *= SpeedBoostMultiplier;
	}

	return MaxSpeed;
}

float UBCharacterMovement::GetMaxAcceleration() const
{
	float MaxAccel = Super::GetMaxAcceleration();

	if (bWantsToSpeedBoost)
	{
		MaxAccel *= SpeedBoostAccelMultiplier;
	}

	return MaxAccel;
}

bool UBCharacterMovement::OnMultiJump()
{
	if (CharacterOwner)
	{
		Velocity.Z = MultiJumpImpulse;
		CurrentMultiJumpCount++;
		return true;
	}

	return false;
}

bool UBCharacterMovement::CanMultiJump()
{
	return (MaxMultiJumpCount > 0) && (CurrentMultiJumpCount < MaxMultiJumpCount);
}

bool UBCharacterMovement::CanJump()
{
	return (IsMovingOnGround() || CanMultiJump()) && CanEverJump();
}

bool UBCharacterMovement::DoJump(bool bReplayingMoves)
{
	bool bResult = false;
	if (CanJump() && (IsFalling()) ? OnMultiJump() : Super::DoJump(bReplayingMoves)) 
	{
		bResult = true;
	}

	return bResult;
}

void UBCharacterMovement::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	CurrentMultiJumpCount = 0;

	Super::ProcessLanded(Hit, remainingTime, Iterations);
}

void FSavedMove_BCharacter::Clear()
{
	Super::Clear();

	bSavedWantsToSpeedBoost = false;

	SavedMultiJumpCount = 0;
}

void FSavedMove_BCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UBCharacterMovement* CharMov = Cast<UBCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{
		bSavedWantsToSpeedBoost = CharMov->bWantsToSpeedBoost;

		SavedMultiJumpCount = CharMov->CurrentMultiJumpCount;
	}
}

uint8 FSavedMove_BCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedWantsToSpeedBoost)
	{
		Result |= FLAG_Custom_0;
	}

	return Result;
}

bool FSavedMove_BCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	if (bSavedWantsToSpeedBoost != ((FSavedMove_BCharacter*)& NewMove)->bSavedWantsToSpeedBoost)
	{
		return false;
	}

	if (SavedMultiJumpCount != ((FSavedMove_BCharacter*)& NewMove)->SavedMultiJumpCount)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

bool FSavedMove_BCharacter::IsImportantMove(const FSavedMovePtr& LastAckedMove) const
{
	return Super::IsImportantMove(LastAckedMove);
}

void FSavedMove_BCharacter::PostUpdate(ACharacter* Character, EPostUpdateMode PostUpdateMode)
{
	Super::PostUpdate(Character, PostUpdateMode);
}

void FSavedMove_BCharacter::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	UBCharacterMovement* CharMov = Cast<UBCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{
		CharMov->bWantsToSpeedBoost = bSavedWantsToSpeedBoost;

		CharMov->CurrentMultiJumpCount = SavedMultiJumpCount;
	}
}

FSavedMovePtr FNetworkPredictionData_Client_BCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_BCharacter());
}
