// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncActions/AsyncAction_PushConfirmScreen.h"

#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText ScreenTitle, FText ScreenMessage)
{
	if (UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr)
	{
		UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();
		Node->OwningWorld					 = World;
		Node->ScreenType					 = ScreenType;
		Node->ScreenTitle					 = ScreenTitle;
		Node->ScreenMessage					 = ScreenMessage;

		Node->RegisterWithGameInstance(World->GetGameInstance());

		return Node;
	}

	return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	UFrontendUISubsystem* FrontendUI = UFrontendUISubsystem::Get(OwningWorld.Get());

	FrontendUI->PushConfirmScreenToModalStackAsync(
		ScreenType,
		ScreenTitle,
		ScreenMessage,
		[this](EConfirmScreenButtonType ClickedButtonType) 
        {
			OnButtonClicked.Broadcast(ClickedButtonType);

			SetReadyToDestroy();
		});
}