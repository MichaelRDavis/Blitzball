// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "BTeamPlayerStart.generated.h"

UCLASS()
class BLITZBALL_API ABTeamPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	ABTeamPlayerStart(const FObjectInitializer& ObjectInitializer);

	/** Which team can start at this point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Team)
	int32 SpawnTeam;
};
