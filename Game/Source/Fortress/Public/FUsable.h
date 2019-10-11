// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FUsable.generated.h"

class AFCharacter;

UCLASS()
class FORTRESS_API AFUsable : public AActor
{
	GENERATED_BODY()
	
public:	
	AFUsable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUsed(AFCharacter* Character);
	void OnUsed_Implementation(AFCharacter* Character);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBeginFocus();
	void OnBeginFocus_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEndFocus();
	void OnEndFocus_Implementation();
};
