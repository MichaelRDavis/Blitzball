// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FUsable.h"
#include "FPickupItem.generated.h"

class AFInventoryItem;

UCLASS(Abstract, Blueprintable)
class FORTRESS_API AFPickupItem : public AFUsable
{
	GENERATED_BODY()
	
public:
	AFPickupItem();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	TSubclassOf<AFInventoryItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	USoundBase* PickupSound;
};
