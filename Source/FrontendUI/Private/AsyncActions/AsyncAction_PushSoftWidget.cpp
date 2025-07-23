// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncActions/AsyncAction_PushSoftWidget.h"

#include "Widgets/Widget_ActivatableBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, TSoftObjectPtr<UWidget_ActivatableBase> InSoftWidgetClass, UPARAM(meta = (Category = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));

	if (const UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr)
	{
		UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
		Node->RegisterWithGameInstance(World);

		return Node;
	}

	return nullptr;
}