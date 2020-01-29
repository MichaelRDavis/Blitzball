// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.

#include "FCReplicatedPhysicsComponent.h"

UFCReplicatedPhysicsComponent::UFCReplicatedPhysicsComponent()
{
	SetIsReplicated(true);
	PrimaryComponentTick.bCanEverTick = true;
}

void UFCReplicatedPhysicsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFCReplicatedPhysicsComponent::SimulateMove(const FSavedMove_Ball& Move)
{

}

FSavedMove_Ball::FSavedMove_Ball()
{

}
