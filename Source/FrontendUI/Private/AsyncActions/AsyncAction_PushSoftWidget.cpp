// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncActions/AsyncAction_PushSoftWidget.h"

#include "Widgets/Widget_ActivatableBase.h"
#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, UPARAM(meta = (Category = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));

	if (UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr)
	{
		UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
		Node->OwningWorld				  = World;
		Node->OwningPC					  = OwningPlayerController;
		Node->SoftWidgetClass			  = InSoftWidgetClass;
		Node->WidgetStackTag			  = InWidgetStackTag;
		Node->bFocusOnNewlyPushedWidget	  = bFocusOnNewlyPushedWidget;

		Node->RegisterWithGameInstance(World);

		return Node;
	}

	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	UFrontendUISubsystem* FrontendUI = UFrontendUISubsystem::Get(OwningWorld.Get());

	FrontendUI->PushSoftWidgetToStackAsync(
		WidgetStackTag, SoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget) {
			switch (InPushState)
			{
				case EAsyncPushWidgetState::OnCreatedBeforePush:
					PushedWidget->SetOwningPlayer(OwningPC.Get());

					OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
					break;

				case EAsyncPushWidgetState::AfterPush:
					AfterPush.Broadcast(PushedWidget);

					if (bFocusOnNewlyPushedWidget)
					{
						if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
						{
							WidgetToFocus->SetFocus();
						}
					}

					SetReadyToDestroy();

					break;
			}
		});
}