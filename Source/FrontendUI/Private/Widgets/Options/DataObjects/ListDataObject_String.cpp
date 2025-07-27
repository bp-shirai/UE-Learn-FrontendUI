// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/DataObjects/ListDataObject_String.h"

void UListDataObject_String::AddDynamicOption(const FString &InStringValue, const FText &InDisplayText)
{
    AvailableOptionsStringArray.Add(InStringValue);
    AvailableOptionsTextArray.Add(InDisplayText);
}

void UListDataObject_String::OnDataObjectInitialized()
{
    if (!AvailableOptionsStringArray.IsEmpty())
    {
        CurrentStringValue = AvailableOptionsStringArray[0];
    }

    // Read from the saved string value and use it to set the CurrentStringValue
    if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
    {
        CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
    }
}

bool UListDataObject_String::TrySetDisplayTextFromStringValue(const FString &InStringValue)
{
    int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);
    if (AvailableOptionsTextArray.IsValidIndex(CurrentFoundIndex))
    {
        CurrentDisplayText = AvailableOptionsTextArray[CurrentFoundIndex];
        return true;
    }
    return false;
}

void UListDataObject_String::AdvanceToNextOption()
{
    if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
    {
        return;
    }

    const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
    const int32 NextIndexDisplay = CurrentDisplayIndex + 1;

    const bool bIsNextIndexValid = AvailableOptionsStringArray.IsValidIndex(NextIndexDisplay);
    if (bIsNextIndexValid)
    {
        CurrentStringValue = AvailableOptionsStringArray[NextIndexDisplay];
    }
    else
    {
        CurrentStringValue = AvailableOptionsStringArray[0];
    }

    TrySetDisplayTextFromStringValue(CurrentStringValue);

    NotifyListDataModifed(this);
}

void UListDataObject_String::BackToPreviousOption() 
{
    if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
    {
        return;
    }

    const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
    const int32 PreviousIndexToDisplay = CurrentDisplayIndex - 1;

    const bool bIsPreviousIndexValid = AvailableOptionsStringArray.IsValidIndex(PreviousIndexToDisplay);
    if (bIsPreviousIndexValid)
    {
        CurrentStringValue = AvailableOptionsStringArray[PreviousIndexToDisplay];
    }
    else
    {
        CurrentStringValue = AvailableOptionsStringArray.Last();
    }

    TrySetDisplayTextFromStringValue(CurrentStringValue);

    NotifyListDataModifed(this);
}
