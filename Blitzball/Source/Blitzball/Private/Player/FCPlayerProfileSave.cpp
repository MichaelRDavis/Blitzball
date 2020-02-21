// Copyright 2018-2019. Gargantuam Games. All Rights Reserved.


#include "FCPlayerProfileSave.h"
#include "BPlayerState.h"
#include "Kismet/GameplayStatics.h"

UFCPlayerProfileSave::UFCPlayerProfileSave()
{
	
}

UFCPlayerProfileSave* UFCPlayerProfileSave::LoadPlayerProfileData(FString SlotName, const int32 UserIndex)
{
	UFCPlayerProfileSave* Result = nullptr;

	if (SlotName.Len() > 0)
	{
		Result = Cast<UFCPlayerProfileSave>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
		if (Result == nullptr)
		{
			Result = Cast<UFCPlayerProfileSave>(UGameplayStatics::CreateSaveGameObject(UFCPlayerProfileSave::StaticClass()));
		}

		Result->SlotName = SlotName;
		Result->UserIndex = UserIndex;
	}

	return Result;
}

void UFCPlayerProfileSave::SavePlayerProfileData()
{
	UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
	bIsDirty = false;
}

void UFCPlayerProfileSave::SaveIfDirty()
{
	if (bIsDirty)
	{
		SavePlayerProfileData();
	}
}

void UFCPlayerProfileSave::SetPlayerProfileName(FString InPlayerProfileName)
{
	PlayerProfileName = InPlayerProfileName;
}

FString UFCPlayerProfileSave::GetPlayerProfileName() const
{
	return PlayerProfileName;
}

void UFCPlayerProfileSave::AddMatchResult(ABPlayerState* PlayerState)
{
	Goals += PlayerState->GetGoals();
	Saves += PlayerState->GetSaves();
}
