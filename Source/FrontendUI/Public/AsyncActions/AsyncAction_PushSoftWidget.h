// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "AsyncAction_PushSoftWidget.generated.h"

class UWidget_ActivatableBase;

/**
 *
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UWidget_ActivatableBase*, PushedWidget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget To Widget Stack"), Category = "Frontend")
	static UAsyncAction_PushSoftWidget* PushSoftWidget(
		const UObject* WorldContextObject,
		APlayerController* OwningPlayerController,
		TSoftObjectPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta = (Category = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;
};
