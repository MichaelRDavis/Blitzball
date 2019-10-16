// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FMonsterAI.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class FORTRESS_API AFMonsterAI : public AAIController
{
	GENERATED_BODY()
	
public:
	AFMonsterAI();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComp;

protected:
	int32 EnemyKeyID;

public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorTreeComp; }
};
