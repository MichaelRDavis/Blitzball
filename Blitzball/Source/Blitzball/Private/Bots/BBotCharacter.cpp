// Copyright 2018-2020. Gargantuam Games. All Rights Reserved.


#include "BBotCharacter.h"
#include "BBotAIController.h"

ABBotCharacter::ABBotCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = ABBotAIController::StaticClass();
}
