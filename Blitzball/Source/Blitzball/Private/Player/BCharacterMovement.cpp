// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacterMovement.h"
#include "GameFramework/Character.h"

UBCharacterMovement::UBCharacterMovement()
{
	MaxWalkSpeed = 900.0f;
	AirControl = 0.25f;
	MaxAcceleration = 3200.0f;
	GroundFriction = 10.0f;
	BrakingFriction = 5.0f;
	BrakingFrictionFactor = 1.0f;
	GravityScale = 1.0f;
	JumpZVelocity = 620.0f;
	SprintSpeed = 1350.0f;
	SprintAcceleration = 500.0f;
	SprintCooldownTime = 2.0f;
	SprintDuration = 0.0f;
	bIsSprinting = false;
	NetworkSmoothingMode = ENetworkSmoothingMode::Exponential;
}

void UBCharacterMovement::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	bIsSprinting = (Flags & FSavedMove_BCharacter::FLAG_Custom_0) != 0;
}

FNetworkPredictionData_Client* UBCharacterMovement::GetPredictionData_Client() const
{
	if (!ClientPredictionData)
	{
		UBCharacterMovement* MutableThis = const_cast<UBCharacterMovement*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_BCharacter(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.0f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.0f;
	}

	return ClientPredictionData;
}

float UBCharacterMovement::GetMaxSpeed() const
{
	return bIsSprinting ? SprintSpeed : Super::GetMaxSpeed();
}

float UBCharacterMovement::GetMaxAcceleration() const
{
	return bIsSprinting ? SprintAcceleration : Super::GetMaxAcceleration();
}
void FSavedMove_BCharacter::Clear()
{
	Super::Clear();

	bSavedIsSprinting = false;
}

void FSavedMove_BCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UBCharacterMovement* CharMov = Cast<UBCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{
		bSavedIsSprinting = CharMov->bIsSprinting;
	}
}

uint8 FSavedMove_BCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedIsSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	return Result;
}

bool FSavedMove_BCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	if (bSavedIsSprinting != ((FSavedMove_BCharacter*)& NewMove)->bSavedIsSprinting)
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
		CharMov->bIsSprinting = bSavedIsSprinting;
	}
}

FSavedMovePtr FNetworkPredictionData_Client_BCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_BCharacter());
}
