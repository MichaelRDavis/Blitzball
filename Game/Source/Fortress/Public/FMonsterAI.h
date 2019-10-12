// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FMonsterAI.generated.h"

class UBehaviorTreeComponent;

UENUM()
enum class EAIState
{
	EIdle UMETA(DisplayName="Idle"),
	ECombat UMETA(DisplayName="Combat")
};

UCLASS()
class FORTRESS_API AFMonsterAI : public AAIController
{
	GENERATED_BODY()
	
public:
	AFMonsterAI();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=AI)
	EAIState AIState;

	UFUNCTION()
	void SetAIState(EAIState NewAIState);

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComp;

public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorTreeComp; }
};
