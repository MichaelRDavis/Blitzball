// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Sight.h"
#include "FMonsterAI.h"
#include "FMonster.h"
#include "FCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_Sight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AFMonsterAI* AIController = Cast<AFMonsterAI>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AFMonster* Monster = Cast<AFMonster>(AIController->GetPawn());
		AFCharacter* Enemy = Cast<AFCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Monster && Enemy)
		{
			const FVector Origin = (Enemy->GetActorLocation() - Monster->GetActorLocation()).GetSafeNormal();
			const float Distance = FVector::DotProduct(Origin, Enemy->GetActorForwardVector());
			const float VisionCone = FMath::Acos(Distance);
			if (Distance < 55.0f)
			{
				
			}
		}
	}
}
