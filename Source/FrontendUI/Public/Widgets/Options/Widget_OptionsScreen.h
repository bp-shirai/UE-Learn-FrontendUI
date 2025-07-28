// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionsScreen.generated.h"

class UOptionsDataRegistry;
class UFrontendTabListWidgetBase;
class UFrontendCommonListView;
class UWidget_OptionsDetailsView;

/**
 *
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_OptionsScreen : public UWidget_ActivatableBase
{
    GENERATED_BODY()

protected:
    //~ Begin UUserWidget Interface
    virtual void NativeOnInitialized() override;
    //~ End UUserWidget Interface

    //~ Begin UCommonActivatableWidget Interface
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    //~ End UCommonActivatableWidget Interface

    UOptionsDataRegistry *GetOrCreateDataRegistry();

private:
    void OnResetBoundActionTriggered();
    void OnBackBoundActionTriggered();

    UFUNCTION()
    void OnOptionsTabSelected(FName TabID);

    void OnListViewItemHovered(UObject *InHoveredItem, bool bWasHovered);
    void OnListViewItemSelected(UObject *InSelectedItem);

    FString TryGetEntryWidgetClassName(UObject *InOwningListItem) const;

    //***** Bound Widgets *****/
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UFrontendTabListWidgetBase> TabListWidget_OptionsTabs;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UFrontendCommonListView> CommonListView_OptionsList;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UWidget_OptionsDetailsView> DetailsView_ListEntryInfo;
    //***** Bound Widgets *****/

    // Handle the creation of data in the options screen. Direct access to this variable is forbidden
    UPROPERTY(Transient)
    TObjectPtr<UOptionsDataRegistry> OwningDataRegistry;

    UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
    FDataTableRowHandle ResetAction;

    FUIActionBindingHandle ResetActionHandle;
};
