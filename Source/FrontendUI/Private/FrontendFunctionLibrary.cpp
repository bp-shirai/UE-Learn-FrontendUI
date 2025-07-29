// Fill out your copyright notice in the Description page of Project Settings.

#include "FrontendFunctionLibrary.h"

#include "FrontendSettings/FrontendDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag)
{
	const UFrontendDeveloperSettings* Settings = GetDefault<UFrontendDeveloperSettings>();

	checkf(Settings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return Settings->FrontendWidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UFrontendFunctionLibrary::GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "Frontend.Image")) FGameplayTag InImageTag)
{
	const UFrontendDeveloperSettings* Settings = GetDefault<UFrontendDeveloperSettings>();

	checkf(Settings->OptionsScreenSoftImageMap.Contains(InImageTag), TEXT("Could not find an image associated with tag %s"), *InImageTag.ToString());

	return Settings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}
