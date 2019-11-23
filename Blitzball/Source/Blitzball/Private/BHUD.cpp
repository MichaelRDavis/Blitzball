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