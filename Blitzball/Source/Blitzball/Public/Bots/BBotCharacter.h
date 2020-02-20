// Copyright 2018-2020. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/BCharacter.h"
#include "BBotCharacter.generated.h"

UCLASS()
class BLITZBALL_API ABBotCharacter : public ABCharacter
{
	GENERATED_BODY()
	
public:
	ABBotCharacter(const FObjectInitializer& ObjectInitializer);
};
