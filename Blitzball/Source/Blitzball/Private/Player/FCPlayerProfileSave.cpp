// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.


#include "FCPlayerProfileSave.h"

void UFCPlayerProfileSave::SetPlayerProfileName(FString InPlayerProfileName)
{
	PlayerProfileName = InPlayerProfileName;
}

FString UFCPlayerProfileSave::GetPlayerProfileName() const
{
	return PlayerProfileName;
}

void UFCPlayerProfileSave::AddMatchResult(int32 Goals, int32 Saves, bool bIsMatchWinner)
{

}
