// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FCharacterMovement.generated.h"

UCLASS()
class FORTRESS_API UFCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UFCharacterMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprint)
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprint)
	float TargetingSpeed;
};
