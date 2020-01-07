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

	}

	return false;
}
