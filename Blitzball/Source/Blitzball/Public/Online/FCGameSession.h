// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "FCGameSession.generated.h"

UCLASS(config=Game)
class BLITZBALL_API AFCGameSession : public AGameSession
{
	GENERATED_BODY()
	
public:
	AFCGameSession();
};
