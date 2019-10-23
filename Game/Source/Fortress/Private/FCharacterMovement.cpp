// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacterMovement.h"
#include "GameFramework/Character.h"

UFCharacterMovement::UFCharacterMovement()
{
	MaxWalkSpeed = 900.0f;
	MaxWalkSpeedCrouched = 300.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintAccelMultiplier = 1.5f;
	bWantsToSprint = false;
	TargetingSpeedMultiplier = 0.5f;
	TargetingAccelMultiplier = 0.5f;
	bIsTargeting = false;
	CurrentJumpCount = 0;
	MaxJumpCount = 1;
	GravJumpImpulse = 600.0f;
	NavAgentProps.bCanCrouch = true;
}

void UFCharacterMovement::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	bWantsToSprint = (Flags&FSavedMove_FCharacter::FLAG_Custom_0) != 0;
	bIsTargeting = (Flags & FSavedMove_FCharacter::FLAG_Custom_1) != 0;
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

void UFCharacterMovement::SetSprinting(bool bNewSprinting)
{
	bWantsToSprint = bNewSprinting;
}

void UFCharacterMovement::SetTargeting(bool bNewTargeting)
{
	bIsTargeting = bNewTargeting;
}

float UFCharacterMovement::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	if (bWantsToSprint)
	{
		MaxSpeed *= SprintSpeedMultiplier;
	}
	else if (bIsTargeting)
	{
		MaxSpeed *= TargetingSpeedMultiplier;
	}

	return MaxSpeed;
}

float UFCharacterMovement::GetMaxAcceleration() const
{
	float MaxAccel = Super::GetMaxAcceleration();

	if (bWantsToSprint)
	{
		MaxAccel *= SprintAccelMultiplier;
	}
	else if (bIsTargeting)
	{
		MaxAccel *= TargetingSpeedMultiplier;
	}

	return MaxAccel;
}

bool UFCharacterMovement::CanJump()
{
	return (IsMovingOnGround() || CurrentJumpCount < MaxJumpCount) && CanEverJump();
}

void UFCharacterMovement::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	CurrentJumpCount = 0;
	
	Super::ProcessLanded(Hit, remainingTime, Iterations);
}

bool UFCharacterMovement::DoJump(bool bReplayingMoves)
{
	if (Super::DoJump(bReplayingMoves))
	{
		CurrentJumpCount++;
		if (CurrentJumpCount > 1)
		{
			Velocity.Z = GravJumpImpulse;
		}
		return true;
	}

	return false;
}

void FSavedMove_FCharacter::Clear()
{
	Super::Clear();

	bSavedWantsToSprint = false;
	bSavedIsTargeting = false;

	SavedJumpCount = 0;
}

void FSavedMove_FCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UFCharacterMovement* CharMov = Cast<UFCharacterMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{
		SavedJumpCount = CharMov->CurrentJumpCount;

		bSavedWantsToSprint = CharMov->bWantsToSprint;
		bSavedIsTargeting = CharMov->bIsTargeting;
	}
}

uint8 FSavedMove_FCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedWantsToSprint)
	{
		Result |= FLAG_Custom_0;
	}

	if (bSavedIsTargeting)
	{
		Result |= FLAG_Custom_1;
	}

	return Result;
}

bool FSavedMove_FCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	if (bSavedWantsToSprint != ((FSavedMove_FCharacter*)& NewMove)->bSavedWantsToSprint)
	{
		return false;
	}

	if (bSavedIsTargeting != ((FSavedMove_FCharacter*)& NewMove)->bSavedIsTargeting)
	{
		return false;
	}

	if (SavedJumpCount != ((FSavedMove_FCharacter*)& NewMove)->SavedJumpCount)
	{
		return false;
	}

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
		CharMov->CurrentJumpCount = SavedJumpCount;

		CharMov->bIsTargeting = bSavedIsTargeting;
		CharMov->bWantsToSprint = bSavedWantsToSprint;
	}
}

FSavedMovePtr FNetworkPredictionData_Client_FCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_FCharacter());
}
