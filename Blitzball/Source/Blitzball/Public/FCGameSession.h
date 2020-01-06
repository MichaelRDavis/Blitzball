// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "GameFramework/GameSession.h"
#include "FCGameSession.generated.h"

UCLASS(config=Game)
class BLITZBALL_API AFCGameSession : public AGameSession
{
	GENERATED_BODY()
	
protected:
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

public:
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPressence, int32 MaxNumPlayers);
};
