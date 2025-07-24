// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Widget_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "ICommonInputModule.h"

#include "Widgets/Components/FrontendCommonButtonBase.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle				 = InScreenTitle;
	InfoObject->ScreenMessage			 = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	OKButtonInfo.ButtonTextToDisplay	 = FText::FromString(TEXT("Ok"));

	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

	return InfoObject;
}
UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle				 = InScreenTitle;
	InfoObject->ScreenMessage			 = InScreenMessage;

	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	YesButtonInfo.ButtonTextToDisplay	  = FText::FromString(TEXT("Yes"));

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Canceled;
	NoButtonInfo.ButtonTextToDisplay	 = FText::FromString(TEXT("No"));

	InfoObject->AvailableScreenButtons.Add(YesButtonInfo);
	InfoObject->AvailableScreenButtons.Add(NoButtonInfo);

	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle				 = InScreenTitle;
	InfoObject->ScreenMessage			 = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	OKButtonInfo.ButtonTextToDisplay	 = FText::FromString(TEXT("Ok"));

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Canceled;
	CancelButtonInfo.ButtonTextToDisplay	 = FText::FromString(TEXT("Cancel"));

	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);
	InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return InfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

	// Checking if the entry box has old button created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		// Clearing the old buttons the entry box has. The widget type for the entry box is specified in the child widget blueprint.
		DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>(
			[](UFrontendCommonButtonBase& ExistingButton) 
            {
				ExistingButton.OnClicked().Clear();
			});
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());

	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;

		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
			case EConfirmScreenButtonType::Confirmed:
				InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultClickAction();
				break;

			case EConfirmScreenButtonType::Canceled:
				InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
				break;

			case EConfirmScreenButtonType::Closed:
				InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
				break;
		}

		UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UFrontendCommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeredInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback, AvailableButtonInfo, this]() 
            {
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);

				DeactivateWidget();
			});
	}

    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        // Set focus on the last button. So if there are two buttons, one is yes, one is no. Our gamepad will focus on the No button
        DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
    }
}