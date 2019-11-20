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

void FSavedMove_BCharacter::Clear()
{
	Super::Clear();
}

void FSavedMove_BCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UBCharacterMovement* CharMov = Cast<UBCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{

	}
}

uint8 FSavedMove_BCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	return Result;
}

bool FSavedMove_BCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
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

	}
}

FSavedMovePtr FNetworkPredictionData_Client_BCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_BCharacter());
}
