// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerCameraManager.h"
#include "FCharacter.h"

AFPlayerCameraManager::AFPlayerCameraManager()
{
	NormalFOV = 90.0f;
	TargetingFOV = 60.0f;
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
	bAlwaysApplyModifiers = true;
}

void AFPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	AFCharacter* Character = PCOwner ? Cast<AFCharacter>(PCOwner->GetPawn()) : nullptr;
	if (Character)
	{
		const float TargetFOV = Character->IsTargeting() ? TargetingFOV : NormalFOV;
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 20.0f);
		SetFOV(DefaultFOV);
	}

	Super::UpdateCamera(DeltaTime);
}
