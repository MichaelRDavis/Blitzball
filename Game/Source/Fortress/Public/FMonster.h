// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FCharacterBase.h"
#include "FMonster.generated.h"

class UBehaviorTree;
class AFWeapon;

UCLASS()
class FORTRESS_API AFMonster : public AFCharacterBase
{
	GENERATED_BODY()
	
public:
	AFMonster(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	UBehaviorTree* MonsterBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	TSubclassOf<AFWeapon> Weapon;
};
