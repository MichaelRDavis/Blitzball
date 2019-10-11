// Fill out your copyright notice in the Description page of Project Settings.

#include "FHUD.h"
#include "Blueprint/UserWidget.h"

AFHUD::AFHUD()
{

}

void AFHUD::BeginPlay()
{
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
