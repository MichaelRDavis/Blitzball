// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FExploder.generated.h"

UCLASS()
class FORTRESS_API AFExploder : public AActor
{
	GENERATED_BODY()
	
public:	
	AFExploder();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	int32 Health;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Actor)
	bool bExploded;
};
