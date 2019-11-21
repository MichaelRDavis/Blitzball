// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacterMovement.h"
#include "GameFramework/Character.h"

UBCharacterMovement::UBCharacterMovement()
{
	MaxFlySpeed = 900.0f;
	ThrustBoostSpeedMultiplier = 1.5f;
	ThurstBoostAccelerationMultiplier = 1.5f;
	bIsThrustBoosting = false;
	DefaultLandMovementMode = EMovementMode::MOVE_Flying;
}

void UBCharacterMovement::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	bIsThrustBoosting = (Flags & FSavedMove_BCharacter::FLAG_Custom_0) != 0;
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

void UBCharacterMovement::SetThrustBoosters(bool bNewThrustBoosters)
{
	bIsThrustBoosting = bNewThrustBoosters;
}

float UBCharacterMovement::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	if (bIsThrustBoosting)
	{
		MaxSpeed *= ThrustBoostSpeedMultiplier;
	}

	return MaxSpeed;
}

float UBCharacterMovement::GetMaxAcceleration() const
{
	float MaxAccel = Super::GetMaxAcceleration();

	if (bIsThrustBoosting)
	{
		MaxAccel *= ThurstBoostAccelerationMultiplier;
	}

	return MaxAccel;
}

void FSavedMove_BCharacter::Clear()
{
	Super::Clear();

	bSavedIsThrustBoosting = false;
}

void FSavedMove_BCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UBCharacterMovement* CharMov = Cast<UBCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{
		bSavedIsThrustBoosting = CharMov->bIsThrustBoosting;
	}
}

uint8 FSavedMove_BCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedIsThrustBoosting)
	{
		Result |= FLAG_Custom_0;
	}

	return Result;
}

bool FSavedMove_BCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	if (bSavedIsThrustBoosting != ((FSavedMove_BCharacter*)&NewMove)->bSavedIsThrustBoosting)
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
		CharMov->bIsThrustBoosting = bSavedIsThrustBoosting;
	}
}

FSavedMovePtr FNetworkPredictionData_Client_BCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_BCharacter());
}
