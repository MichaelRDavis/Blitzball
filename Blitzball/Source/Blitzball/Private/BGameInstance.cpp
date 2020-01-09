// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameInstance.h"

UBGameInstance::UBGameInstance()
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UBGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UBGameInstance::OnStartOnlineGameComplete);
}

void UBGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	
}

void UBGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{

}

bool UBGameInstance::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPressence, int32 MaxNumPlayers)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && UserId->IsValid())
		{
			SessionSettings = MakeShareable(new FOnlineSessionSettings());
			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPressence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings->Set(SETTING_MAPNAME, FString("NewMap"), EOnlineDataAdvertisementType::ViaOnlineService);

			OnCreateSessionCompleteHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
		}
	}
	else
	{
		// TOOD: Log message that no OnlineSubystem could be found
	}

	return false;
}
