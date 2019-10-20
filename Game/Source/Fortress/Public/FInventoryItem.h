// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FInventoryItem.generated.h"

UENUM()
enum class EItemRarity
{
	ECommon UMETA(DisplayName="Common"),
	EUncommon UMETA(DisplayName = "Uncommon"),
	ERare UMETA(DisplayName = "Rare"),
	ELegendary UMETA(DisplayName = "Legendary"),
	EExotic UMETA(DisplayName = "Exotic")
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable;

	FItemData()
	{
		StackCount = 0;
		MaxStackCount = 10;
		bIsStackable = true;
	}
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	EItemRarity ItemRarity;

	void GivenTo(AFCharacter* NewOwner);
	void Removed();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	bool CanItemStack();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void CheckForStack();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	int32 ItemCount;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	AFCharacter* FOwner;
};
