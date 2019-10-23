// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPickup.generated.h"

class USphereComponent;
class AFCharacter;

UCLASS(Abstract, Blueprintable)
class FORTRESS_API AFPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPickup();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	USphereComponent* CollisionComp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void PickupOnOverlap(AFCharacter* Pawn);

	UFUNCTION()
	virtual void GiveTo(AFCharacter* Pawn);

	/** Sound played on pick up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	USoundBase* PickupSound;

	/** Sound played on respawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	USoundBase* RespawnSound;

	/** Respawn time for the pickup */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Pickup)
	float RespawnTime;

	FTimerHandle RespawnTimer;
};
