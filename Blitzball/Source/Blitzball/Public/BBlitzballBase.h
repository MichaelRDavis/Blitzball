// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBlitzballBase.generated.h"

class ABBlitzball;

UCLASS()
class BLITZBALL_API ABBlitzballBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABBlitzballBase();

	virtual void BeginPlay() override;

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerSpawnBlitzball();
	void ServerSpawnBlitzball_Implementation();
	bool ServerSpawnBlitzball_Validate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameObject)
	TSubclassOf<ABBlitzball> BlitzballClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GameObject)
	ABBlitzball* Blitzball;
};
