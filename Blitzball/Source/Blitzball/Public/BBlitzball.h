// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBlitzball.generated.h"

class USphereComponent;
class ABCharacter;
class ABPlayerState;
class ABBlitzballBase;

UCLASS()
class BLITZBALL_API ABBlitzball : public AActor
{
	GENERATED_BODY()
	
public:	
	ABBlitzball();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetLastPlayer(ABCharacter* NewPlayer);

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void Score();

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void TeleportHome();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlitzballMesh;

public:
	/** Reference to pawn that last hit this object */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = GameObject)
	ABCharacter* Pawn;

	/** Reference to player that last hit this object */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = GameObject)
	ABPlayerState* Player;

	/** Reference to the last player that hit this object */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = GameObject)
	ABPlayerState* LastPlayer;

	UPROPERTY(BlueprintReadOnly, Category = GameObject)
	float HitTime;

	/** Sound played on hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	USoundBase* HitSound;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = GameObject)
	ABBlitzballBase* HomeBase;
};
