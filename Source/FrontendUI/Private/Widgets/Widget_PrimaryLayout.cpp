// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Widget_PrimaryLayout.h"

#include "FrontendDebugHelper.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InStackTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InStackTag), TEXT("Can not find the widget stack by the tag %s"), *InStackTag.ToString());

	return RegisteredWidgetStackMap.FindRef(InStackTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(UPARAM(meta = (Category = "Frontend.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);

			// Debug::Print(TEXT("Widget Stack Registered under the tag ") + InStackTag.ToString());
		}
	}
}
