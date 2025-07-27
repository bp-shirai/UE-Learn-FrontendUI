// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"

#include "CommonTextBlock.h"

#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

    OnOwningListDataObjectSet(CastChecked<UListDataObject_Base>(ListItemObject));
}

void UWidget_ListEntry_Base::OnOwningListDataObjectSet(UListDataObject_Base *InOwningListDataObject)
{
    if (CommonText_SettingDisplayName)
    {
        CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
    }

    if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
    {
        InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwingListDataObjectModified);
    }
}

void UWidget_ListEntry_Base::OnOwingListDataObjectModified(UListDataObject_Base *OwningModifiedData, EOptionsListDataModifyReason ModifyReason) {}
