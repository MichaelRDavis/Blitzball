// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacterMovement.h"
#include "GameFramework/Character.h"

UFCharacterMovement::UFCharacterMovement()
{

}

void UFCharacterMovement::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
}

FNetworkPredictionData_Client* UFCharacterMovement::GetPredictionData_Client() const
{
	if (!ClientPredictionData)
	{
		UFCharacterMovement* MutableThis = const_cast<UFCharacterMovement*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_FCharacter(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.0f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.0f;
	}

	return ClientPredictionData;
}

void FSavedMove_FCharacter::Clear()
{
	Super::Clear();
}

void FSavedMove_FCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UFCharacterMovement* CharMov = Cast<UFCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{

	}
}

uint8 FSavedMove_FCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	return Result;
}

bool FSavedMove_FCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

bool FSavedMove_FCharacter::IsImportantMove(const FSavedMovePtr& LastAckedMove) const
{
	return Super::IsImportantMove(LastAckedMove);
}

void FSavedMove_FCharacter::PostUpdate(ACharacter* Character, EPostUpdateMode PostUpdateMode)
{
	Super::PostUpdate(Character, PostUpdateMode);
}

void FSavedMove_FCharacter::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	UFCharacterMovement* CharMov = Cast<UFCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{

	}
}

FSavedMovePtr FNetworkPredictionData_Client_FCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_FCharacter());
}
