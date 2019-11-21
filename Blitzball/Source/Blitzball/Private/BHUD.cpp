// Fill out your copyright notice in the Description page of Project Settings.

#include "BHUD.h"
#include "Blueprint/UserWidget.h"

ABHUD::ABHUD()
{

}

void ABHUD::DrawHUD()
{
	Super::DrawHUD();

	if (HUDWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
