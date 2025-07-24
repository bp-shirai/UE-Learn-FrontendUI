// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FrontendTypes/FrontendEnumTypes.h"
#include "AsyncAction_PushConfirmScreen.generated.h"

/**
 *
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, EConfirmScreenButtonType, ClickedButtonType);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Show Confirmation Screen"), Category = "Frontend")
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		EConfirmScreenType ScreenType,
		FText ScreenTitle,
		FText ScreenMessage);

	//~ Begin UBlueprintAsyncActionBase Interface
	virtual void Activate() override;
	//~ End UBlueprintAsyncActionBase Interface

	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnButtonClicked;

private:
	TWeakObjectPtr<UWorld> OwningWorld;
	EConfirmScreenType ScreenType;
	FText ScreenTitle;
	FText ScreenMessage;
};
