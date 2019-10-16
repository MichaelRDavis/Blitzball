// Fill out your copyright notice in the Description page of Project Settings.

#include "FMonsterAI.h"
#include "FMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AFMonsterAI::AFMonsterAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BrainComponent = BehaviorTreeComp;
}

void AFMonsterAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AFMonster* Monster = Cast<AFMonster>(InPawn);
	if (Monster && Monster->MonsterBehavior)
	{
		if (Monster->MonsterBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Monster->MonsterBehavior->BlackboardAsset);
		}

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");

		BehaviorTreeComp->StartTree(*(Monster->MonsterBehavior));
	}
}

void AFMonsterAI::OnUnPossess()
{
	Super::OnUnPossess();

	BehaviorTreeComp->StopTree();
}
