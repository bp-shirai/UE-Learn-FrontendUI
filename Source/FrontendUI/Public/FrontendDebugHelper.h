#pragma once

#include "CoreMinimal.h"

// Declare a new log category
DECLARE_LOG_CATEGORY_EXTERN(LogFrontend, Log, All);

namespace Debug
{
    static void Print(const FString& Msg, int32 InKey = -1, const FColor& InColor = FColor::MakeRandomColor(), bool bPrintScreen = true)
    {
        if (GEngine)
        {
            if (bPrintScreen) GEngine->AddOnScreenDebugMessage(InKey, 7.f, InColor, Msg);

            UE_LOG(LogFrontend, Warning, TEXT("%s"), *Msg);
        }
    }
}