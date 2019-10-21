// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};

class AFCharacter;

UCLASS()
class FORTRESS_API AFInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AFInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	FItemData ItemData;

	void GivenTo(AFCharacter* NewOwner);
	void Removed();

protected:
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	AFCharacter* FOwner;
};
