// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/Widget_OptionsScreen.h"

#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"

#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/Widget_OptionsDetailsView.h"
#include "Widgets/Components/FrontendTabListWidgetBase.h"
#include "Widgets/Components/FrontendCommonListView.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "FrontendDebugHelper.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (!ResetAction.IsNull())
    {
        ResetActionHandle = RegisterUIActionBinding(FBindUIActionArgs(ResetAction, true, FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)));
    }

    RegisterUIActionBinding(FBindUIActionArgs(ICommonInputModule::GetSettings().GetDefaultBackAction(), true, FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)));

    TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);

    CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
    CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
}

void UWidget_OptionsScreen::NativeOnActivated()
{
    Super::NativeOnActivated();

    for (UListDataObject_Collection *TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
    {
        if (!TabCollection)
        {
            continue;
        }

        const FName TabID = TabCollection->GetDataID();
        if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID) != nullptr)
        {
            continue;
        }

        TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
    }
}

UOptionsDataRegistry *UWidget_OptionsScreen::GetOrCreateDataRegistry()
{
    if (!OwningDataRegistry)
    {
        OwningDataRegistry = NewObject<UOptionsDataRegistry>();
        OwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
    }
    checkf(OwningDataRegistry, TEXT("Data registry for options screen is not valid"));

    return OwningDataRegistry;
}

void UWidget_OptionsScreen::OnResetBoundActionTriggered() { Debug::Print(TEXT("Reset bound action triggered")); }

void UWidget_OptionsScreen::OnBackBoundActionTriggered() { DeactivateWidget(); }

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabID)
{
    TArray<UListDataObject_Base *> FoundListSourceItem = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabID);

    CommonListView_OptionsList->SetListItems(FoundListSourceItem);

    if (CommonListView_OptionsList->GetNumItems() != 0)
    {
        CommonListView_OptionsList->NavigateToIndex(0);
        CommonListView_OptionsList->SetSelectedIndex(0);
        CommonListView_OptionsList->RequestRefresh();
    }
}

void UWidget_OptionsScreen::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    // UFrontendGameUserSettings::Get()->ApplySettings(true);
    UFrontendGameUserSettings::Get()->ApplyNonResolutionSettings();
}

void UWidget_OptionsScreen::OnListViewItemHovered(UObject *InHoveredItem, bool bWasHovered)
{
    if (!InHoveredItem)
        return;

    UWidget_ListEntry_Base *HoveredEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem<UWidget_ListEntry_Base>(InHoveredItem);

    check(HoveredEntryWidget);

    HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

    if (bWasHovered)
    {
        DetailsView_ListEntryInfo->UpdateDetailsViewInfo(CastChecked<UListDataObject_Base>(InHoveredItem), TryGetEntryWidgetClassName(InHoveredItem));
    }
    else
    {
        if (UListDataObject_Base *SelectedItem = CommonListView_OptionsList->GetSelectedItem<UListDataObject_Base>())
        {
            DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
        }
    }
}

void UWidget_OptionsScreen::OnListViewItemSelected(UObject *InSelectedItem)
{
    if (!InSelectedItem)
        return;
        
    DetailsView_ListEntryInfo->UpdateDetailsViewInfo(CastChecked<UListDataObject_Base>(InSelectedItem), TryGetEntryWidgetClassName(InSelectedItem));
}

FString UWidget_OptionsScreen::TryGetEntryWidgetClassName(UObject *InOwningListItem) const
{
    if (UUserWidget *FoundEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
    {
        return FoundEntryWidget->GetClass()->GetName();
    }
    return TEXT("Entry Widget Not Valid");
}
