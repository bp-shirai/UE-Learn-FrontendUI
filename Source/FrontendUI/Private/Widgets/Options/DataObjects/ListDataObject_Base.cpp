// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Base.h"


void UListDataObject_Base::InitDataObject()
{
    OnDataObjectInitialized();
}

void UListDataObject_Base::OnDataObjectInitialized()
{
}
void UListDataObject_Base::NotifyListDataModifed(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    OnListDataModified.Broadcast(ModifiedData, ModifyReason);
}
