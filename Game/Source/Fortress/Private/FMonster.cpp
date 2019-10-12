// Fill out your copyright notice in the Description page of Project Settings.

#include "FMonster.h"
#include "FMonsterAI.h"

AFMonster::AFMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AFMonsterAI::StaticClass();
}
