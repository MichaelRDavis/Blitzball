// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FCReplicatedPhysicsComponent.generated.h"

class ABBlitzball;

class BLITZBALL_API FSavedMove_Ball
{
public:
	FSavedMove_Ball();

	ABBlitzball* ActorOwner;

	float TimeStamp;
	float DeltaTime;

	FVector Velocity;
	FRotator Rotation;
};

UCLASS()
class BLITZBALL_API UFCReplicatedPhysicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFCReplicatedPhysicsComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FSavedMove_Ball& Move);

protected:
	/** Replicated physics component belongs to */
	UPROPERTY(Transient, DuplicateTransient)
	ABBlitzball* Actor;

public:
	FSavedMove_Ball LastMove;
};