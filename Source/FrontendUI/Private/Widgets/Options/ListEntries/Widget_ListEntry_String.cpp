// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/ListEntries/Widget_ListEntry_String.h"

#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Components/FrontendCommonRotator.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"

void UWidget_ListEntry_String::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    CommonButton_PreviousOption->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
    CommonButton_NextOption->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);
}

void UWidget_ListEntry_String::OnOwningListDataObjectSet(UListDataObject_Base *InOwningListDataObject)
{
    Super::OnOwningListDataObjectSet(InOwningListDataObject);

    OwningStringDataObject = CastChecked<UListDataObject_String>(InOwningListDataObject);

    CommonRotator_AvailableOptions->PopulateTextLabels(OwningStringDataObject->GetAvailableOptionsTextArray());
    CommonRotator_AvailableOptions->SetSelectedOptionByText(OwningStringDataObject->GetCurrentDisplayText());
}

void UWidget_ListEntry_String::OnPreviousOptionButtonClicked()
{
    if (auto DataObject = OwningStringDataObject.Get())
    {
        DataObject->BackToPreviousOption();
    }
}

void UWidget_ListEntry_String::OnNextOptionButtonClicked()
{
    if (auto DataObject = OwningStringDataObject.Get())
    {
        DataObject->AdvanceToNextOption();
    }
}

void UWidget_ListEntry_String::OnOwingListDataObjectModified(UListDataObject_Base *OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    if (auto DataObject = OwningStringDataObject.Get())
    {
        CommonRotator_AvailableOptions->SetSelectedOptionByText(DataObject->GetCurrentDisplayText());
    }
}
