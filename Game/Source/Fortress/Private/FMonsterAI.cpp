// Fill out your copyright notice in the Description page of Project Settings.

#include "FMonsterAI.h"
#include "FMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AFMonsterAI::AFMonsterAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BrainComponent = BehaviorTreeComp;

	AIState = EAIState::EIdle;
}

void AFMonsterAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AFMonster* Monster = Cast<AFMonster>(InPawn);
	if (Monster && Monster->MonsterBehavior)
	{

	}
}

void AFMonsterAI::SetAIState(EAIState NewAIState)
{
	AIState = NewAIState;
}
