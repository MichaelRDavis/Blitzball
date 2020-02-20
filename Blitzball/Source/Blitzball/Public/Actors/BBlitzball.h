// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBlitzball.generated.h"

class USphereComponent;
class ABCharacter;
class ABPlayerState;
class ABPlayerController;
class ABBlitzballBase;
class ABGoal;
class UFCReplicatedPhysicsComponent;

UCLASS()
class BLITZBALL_API ABBlitzball : public AActor
{
	GENERATED_BODY()
	
public:	
	ABBlitzball();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* MyComp, UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* HitComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category=GameObject)
	void SetLastPlayer(ABCharacter* NewPlayer);

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void Score(int32 TeamNumber);

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void SpawnAtBase();

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void HeaderBall(AActor* OtherActor, FVector HitLocation);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerHeaderBall(AActor* OtherActor, FVector HitLocation);
	void ServerHeaderBall_Implementation(AActor* OtherActor, FVector HitLocation);
	bool ServerHeaderBall_Validate(AActor* OtherActor, FVector HitLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlitzballMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Physics, meta=(AllowPrivateAccess="true"))
	UFCReplicatedPhysicsComponent* PhysicsReplication;

public:
	/** Reference to pawn that last hit this object */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = GameObject)
	ABCharacter* Pawn;

	/** Reference to player state that last hit this object */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = GameObject)
	ABPlayerState* Player;

	/** Reference to the last player state that hit this object */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = GameObject)
	ABPlayerState* LastPlayer;

	/** Reference to player controller that hit this ball */
	UPROPERTY(BlueprintReadOnly, Replicated, Category=GameObject)
	ABPlayerController* PlayerController;

	/** Time ball was hit */
	UPROPERTY(BlueprintReadOnly, Category = GameObject)
	float HitTime;

	/** True if ball was kicked */
	UPROPERTY(BlueprintReadOnly, Category = GameObject)
	bool bIsHit;

	/** Impulse applied to ball when headed by the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameObject)
	float HeaderImpulse;

	/** Sound played on hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* HitSound;

	/** Sound played on header */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* HeaderSound;

	/** Spawn location for ball */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = GameObject)
	ABBlitzballBase* HomeBase;

	inline USphereComponent* GetCollisionComp() const
	{
		return CollisionComp;
	}
};
