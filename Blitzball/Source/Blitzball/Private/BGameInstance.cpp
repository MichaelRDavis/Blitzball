// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameInstance.h"

UBGameInstance::UBGameInstance()
{

}

void UBGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{

}

void UBGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{

}

bool UBGameInstance::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPressence, int32 MaxNumPlayers)
{
	return true;
}
