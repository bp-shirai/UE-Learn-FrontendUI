// Fill out your copyright notice in the Description page of Project Settings.

#include "FrontendSettings/FrontendGameUserSettings.h"

#include "Engine.h"

UFrontendGameUserSettings *UFrontendGameUserSettings::Get() 
{ 
    return GEngine ? CastChecked<UFrontendGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr; 
}
