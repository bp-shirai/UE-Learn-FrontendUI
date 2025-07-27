// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UFrontendCommonButtonBase;
class UFrontendCommonRotator;
class UListDataObject_String;

/**
 *
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
    GENERATED_BODY()

protected:
    //~ Begin UUserWidget Interface
    virtual void NativeOnInitialized() override;
    //~ End UUserWidget Interface

    //~ Begin UWidget_ListEntry_Base Interface
    virtual void OnOwningListDataObjectSet(UListDataObject_Base *InOwningListDataObject) override;
    virtual void OnOwingListDataObjectModified(UListDataObject_Base *OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
    //~ End UWidget_ListEntry_Base Interface

private:
    void OnPreviousOptionButtonClicked();
    void OnNextOptionButtonClicked();

    //**** Bound Widgets ****//
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
    TObjectPtr<UFrontendCommonButtonBase> CommonButton_PreviousOption;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
    TObjectPtr<UFrontendCommonRotator> CommonRotator_AvailableOptions;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
    TObjectPtr<UFrontendCommonButtonBase> CommonButton_NextOption;
    //**** Bound Widgets ****//

    UPROPERTY(Transient)
    TWeakObjectPtr<UListDataObject_String> OwningStringDataObject;
};
