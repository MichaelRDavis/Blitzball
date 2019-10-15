// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.h"
#include "FGrenade.generated.h"

class AFProj_Grenade;

UCLASS()
class FORTRESS_API AFGrenade : public AFInventoryItem
{
	GENERATED_BODY()
	
public:
	AFGrenade();

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = Grenade)
	void SpawnGrenade();

	UPROPERTY(BlueprintReadOnly, Category = Grenade)
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grenade)
	int32 MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grenade)
	FVector SpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grenade)
	TSubclassOf<AFProj_Grenade> GrenadeClass;
};
