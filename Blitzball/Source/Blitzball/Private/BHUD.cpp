// Fill out your copyright notice in the Description page of Project Settings.

#include "BHUD.h"
#include "Blueprint/UserWidget.h"

ABHUD::ABHUD()
{

}

void ABHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

FString ABHUD::GetTime(int32 Time)
{
	const int32 TotalSeononds = FMath::Max(0, FMath::TruncToInt(Time) % 3600);
	const int32 NumMinutes = TotalSeononds / 60;
	const int32 NumSeconds = TotalSeononds % 60;

	const FString TimeDesc = FString::Printf(TEXT("%02d:%02d"), NumMinutes, NumSeconds);
	return TimeDesc;
}
