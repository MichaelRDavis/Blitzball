// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ABBlitzball;
class UBCharacterMovement;

UCLASS(Abstract, config=Game)
class BLITZBALL_API ABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABCharacter(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Begin ACharacter interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;
	virtual void PawnClientRestart() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	// End ACharacter interface

	/** Cached FCCharacterMovement casted CharacterMovement */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	UBCharacterMovement* BCharacterMovement;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Collision capsule for ball collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CollisionComp;

public:
	/** Handles moving forward */
	void MoveForward(float Value);

	/** Handles strafing movement left and right */
	void MoveRight(float Value);

	/** Make the character sprint */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StartSprinting();

	/** Stop the character from sprinting */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void StopSprinting();

	/** True if player can sprint this frame */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Pawn)
	bool CanSprint();

	/** True if currently sprinting */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	bool IsSprinting() const;

	/** True if currently jumping */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	bool IsJumping() const;

	/** Update team outline colors for player mesh */
	void UpdateTeamColors();

	/** Kick ball if within character collision */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void Kick();

	/** Server kick ball implementation */
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerKick();
	void ServerKick_Implementation();
	bool ServerKick_Validate();

	/** Impulse applied to ball in current possession when kicked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pawn)
	float KickImpulse;

	/** Ball in current player possession */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawm)
	ABBlitzball* PossesedBall;

	/** Get the ball currently in player possession */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	ABBlitzball* GetPossesedBall() const;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Emote currently playing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emote)
	UAnimMontage* CurrentEmote;

	/** Play emote */
	UFUNCTION(BlueprintCallable, Category = Emote)
	void PlayEmote(UAnimMontage* EmoteToPlay);

	/** Reset emote */
	UFUNCTION()
	void ResetEmote(UAnimMontage* Montage, bool bInterrupted);

	/** True if currently plying an emote */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Emote)
	bool bIsPlayingEmote;

protected:
	/** Play footstep sound */
	UFUNCTION(BlueprintCallable, Category = Effects)
	void PlayFootstep();

	/** Sound to play on footstep */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* FootstepSound;

	/** Play kick effects */
	UFUNCTION(BlueprintCallable, Category = Effects)
	void PlayKick();

	/** Sound to play on kick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* KickSound;

private:
	/** Last time footstep sound was played */
	float LastFootStepTime;

public:
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
