// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Options/OptionsDataRegistry.h"

#include "Engine/LocalPlayer.h"
#include "Misc/AssertionMacros.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
	MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UFrontendGameUserSettings, SetterOrGetterFuncName))

void UOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer *InOwningLocalPlayer)
{
    InitGameplayCollectionTab();
    InitAudioCollectionTab();
    InitVideoCollectionTab();
    InitControlCollectionTab();
}

TArray<UListDataObject_Base *> UOptionsDataRegistry::GetListSourceItemsBySelectedTabID(const FName &InSelectedTabID) const
{
    auto FoundTabCollectionPtr = RegisteredOptionsTabCollections.FindByPredicate([InSelectedTabID](UListDataObject_Collection *AvailableTabCollection) -> bool { return AvailableTabCollection->GetDataID() == InSelectedTabID; });
    checkf(FoundTabCollectionPtr, TEXT("No valid tab found under the ID %s"), *InSelectedTabID.ToString());

    UListDataObject_Collection *FoundTabCollection = *FoundTabCollectionPtr;

    return FoundTabCollection->GetAllChildListData();
}

void UOptionsDataRegistry::InitGameplayCollectionTab()
{
    UListDataObject_Collection *GameplayTabCollection = NewObject<UListDataObject_Collection>();
    GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
    GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));

	// This is the full code for constructor data interactor helper
	/*     
	TSharedPtr<FOptionsDataInteractionHelper> ConstructedHelper = MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UFrontendGameUserSettings, GetCurrentGameDifficulty));
 	*/    
 
 	// Game Difficulty
    {
        UListDataObject_String *GameDifficulty = NewObject<UListDataObject_String>();
        GameDifficulty->SetDataID(FName("GameDifficulty"));
        GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Difficulty")));
        GameDifficulty->SetDescriptionRichText(FText::FromString(TEXT("Adjust the difficulty of the game experience. \n\n<bold>Easy:</> Focuses on the story experience. Prodes the most relaxing combat.\n\n<bold>Normal:</> Offers slightly harder combat experience.\n\n<bold>Hard:</> Offers a much more challenging combat experience. Not recommended for first play through.")));
        GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("Easy")));
        GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
        GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("Hard")));
        GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("Very Hard")));
        GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentGameDifficulty));
        GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentGameDifficulty));
		GameDifficulty->SetShouldApplySettingsImmediately(true);

        GameplayTabCollection->AddChildListData(GameDifficulty);
    }

    // Test Item
    {
        UListDataObject_String *TestItem = NewObject<UListDataObject_String>();
        TestItem->SetDataID(FName("TestItem"));
        TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Item")));
        TestItem->SetDescriptionRichText(FText::FromString(TEXT("Test description text...\n\nPlease don't mind, as it is still under development.")));
        GameplayTabCollection->AddChildListData(TestItem);
    }

    // Test Item
    {
        UListDataObject_String *TestItem = NewObject<UListDataObject_String>();
        TestItem->SetDataID(FName("TestItem2"));
        TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Item 2")));
        TestItem->SetDescriptionRichText(FText::FromString(TEXT("Test description test messages...")));
        GameplayTabCollection->AddChildListData(TestItem);
    }

    RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionsDataRegistry::InitAudioCollectionTab()
{
    UListDataObject_Collection *AudioTabCollection = NewObject<UListDataObject_Collection>();
    AudioTabCollection->SetDataID(FName("AudioTabCollection"));
    AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

    RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionsDataRegistry::InitVideoCollectionTab()
{
    UListDataObject_Collection *VideoTabCollection = NewObject<UListDataObject_Collection>();
    VideoTabCollection->SetDataID(FName("VideoTabCollection"));
    VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

    RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionsDataRegistry::InitControlCollectionTab()
{
    UListDataObject_Collection *ControlTabCollection = NewObject<UListDataObject_Collection>();
    ControlTabCollection->SetDataID(FName("ControlTabCollection"));
    ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

    RegisteredOptionsTabCollections.Add(ControlTabCollection);
}
