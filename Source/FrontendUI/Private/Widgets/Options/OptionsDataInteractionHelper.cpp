// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "PropertyPathHelpers.h"

FOptionsDataInteractionHelper::FOptionsDataInteractionHelper(const FString &InSetterOrGetterFuncPath) : DynamicFunctionPath(InSetterOrGetterFuncPath) { GameUserSettings = UFrontendGameUserSettings::Get(); }

FString FOptionsDataInteractionHelper::GetValueAsString() const
{
    FString OutStringValue;
    PropertyPathHelpers::GetPropertyValueAsString(GameUserSettings.Get(), DynamicFunctionPath, OutStringValue);

    return OutStringValue;
}

void FOptionsDataInteractionHelper::SetValueFromString(const FString &InStringValue) { PropertyPathHelpers::SetPropertyValueFromString(GameUserSettings.Get(), DynamicFunctionPath, InStringValue); }
