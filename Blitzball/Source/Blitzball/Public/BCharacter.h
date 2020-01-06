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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;
	virtual void PawnClientRestart() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

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

	/** Cached FCCharacterMovement casted CharacterMovement */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UBCharacterMovement* BCharacterMovement;

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

	/** Update team outline colors for player mesh */
	void UpdateTeamColors();

	/** Kick ball if within character collision */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	void Kick();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerKick();
	void ServerKick_Implementation();
	bool ServerKick_Validate();

	/** Ball in current player possession */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawm)
	ABBlitzball* PossesedBall;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Pawn)
	ABBlitzball* GetPossesedBall() const;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emote)
	UAnimMontage* CurrentEmote;

	UFUNCTION(BlueprintCallable, Category = Emote)
	void PlayEmote(UAnimMontage* EmoteToPlay);

	UFUNCTION()
	void ResetEmote(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Emote)
	bool bIsPlayingEmote;

protected:
	UFUNCTION(BlueprintCallable, Category = Effects)
	void PlayFootstep();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* FootstepSound;

	UFUNCTION(BlueprintCallable, Category = Effects)
	void PlayKick();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* KickSound;

private:
	float LastFootStepTime;

public:
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
