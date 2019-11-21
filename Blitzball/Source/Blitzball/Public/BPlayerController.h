// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPlayerControllerBase.h"
#include "BPlayerController.generated.h"

class ABCharacter;

UCLASS()
class BLITZBALL_API ABPlayerController : public ABPlayerControllerBase
{
	GENERATED_BODY()
	
public:
	ABPlayerController();

	virtual void SetPawn(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	ABCharacter* BCharacter;

protected:
	/** Handles moving forward */
	void MoveForward(float Value);

	/** Handles moving backward */
	void MoveBackward(float Value);

	/** Handles strafing movement right */
	void MoveRight(float Value);

	/** Handles strafing movement left */
	void MoveLeft(float Value);

	/** Frame rate independent turn */
	void TurnAtRate(float Rate);

	/** Frame rate independent look up */
	void LookUpAtRate(float Rate);

	/** Jumping */
	void OnJump();
	void OnStopJumping();

	/** Firing */
	void OnStartFire();
	void OnStopFire();
	void OnStartAltFire();
	void OnStopAltFire();

	/** Thrust boosters */
	void OnStartSpeedBoost();
	void OnStopSpeedBoost();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
};
