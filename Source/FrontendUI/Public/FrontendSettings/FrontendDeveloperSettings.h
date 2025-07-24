// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "FrontendDeveloperSettings.generated.h"

class UWidget_ActivatableBase;
/**
 *
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Frontend UI Settings"))
class FRONTENDUI_API UFrontendDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableBase>> FrontendWidgetMap;
};
