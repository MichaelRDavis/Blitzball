// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BHUD.generated.h"

UCLASS()
class BLITZBALL_API ABHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ABHUD();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UFUNCTION(BlueprintCallable, Category = HUD)
	FString GetTime(int32 Time);
};
