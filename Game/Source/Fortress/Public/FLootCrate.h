// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FUsable.h"
#include "FLootCrate.generated.h"

class AFPickup;

UCLASS()
class FORTRESS_API AFLootCrate : public AFUsable
{
	GENERATED_BODY()
	
public:
	AFLootCrate();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* CrateMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	float DropChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	TSubclassOf<AFPickup> DropType;

	UFUNCTION(BlueprintCallable, Category = Actor)
	void SpawnLoot();
};
