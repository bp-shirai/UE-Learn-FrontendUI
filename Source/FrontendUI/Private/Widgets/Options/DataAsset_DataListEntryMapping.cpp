// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/DataAsset_DataListEntryMapping.h"

#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"

TSubclassOf<UWidget_ListEntry_Base> UDataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject(UListDataObject_Base *InDataObject) const
{
    check(InDataObject);

    for (UClass *DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
    {
        if (TSubclassOf<UListDataObject_Base> ConvertedDataObjectClass = TSubclassOf<UListDataObject_Base>(DataObjectClass))
        {
            if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
            {
                return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
            }
        }
    }

    return TSubclassOf<UWidget_ListEntry_Base>();
}
