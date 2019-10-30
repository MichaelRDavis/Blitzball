// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPlayerController.generated.h"

class AFCharacter;

UCLASS(config=Game)
class FORTRESS_API AFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFPlayerController();

	virtual void SetPawn(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	virtual void UnFreeze() override;

private:
	UPROPERTY()
	AFCharacter* FCharacter;

protected:
	/** Handles moving forward */
	virtual void MoveForward(float Value);

	/** Handles moving backward */
	virtual void MoveBackward(float Value);

	/** Handles strafing movement right */
	virtual void MoveRight(float Value);

	/** Handles strafing movement left */
	virtual void MoveLeft(float Value);

	virtual void Jump();
	virtual void StopJumping();

	virtual void Sprint();
	virtual void StopSprinting();

	virtual void Crouch();
	virtual void UnCrouch();
	virtual void ToggleCrouch();

	virtual void OnUse();

	virtual void OnStartFire();
	virtual void OnStopFire();

	virtual void OnStartTargeting();
	virtual void OnStopTargeting();

	virtual void OnReload();
};
