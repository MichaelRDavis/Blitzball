// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FCharacterBase.h"
#include "FMonster.generated.h"

UCLASS()
class FORTRESS_API AFMonster : public AFCharacterBase
{
	GENERATED_BODY()
	
public:
	AFMonster(const FObjectInitializer& ObjectInitializer);
};
