// Copyright 2018-2020. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FCActorWidgetComponent.generated.h"

UCLASS()
class BLITZBALL_API UFCActorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFCActorWidgetComponent();
	
	virtual void InitWidget() override;
};
