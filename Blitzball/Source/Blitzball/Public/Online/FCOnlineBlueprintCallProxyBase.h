// Copyright 2018-2020. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FCOnlineBlueprintCallProxyBase.generated.h"

/**
 * 
 */
UCLASS()
class BLITZBALL_API UFCOnlineBlueprintCallProxyBase : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
};
