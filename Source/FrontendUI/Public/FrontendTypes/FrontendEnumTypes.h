#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
    OK,
    YesNo,
    OKCancel,
    Unkown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
    Confirmed,
    Canceled,
    Closed,
    Unkown UMETA(Hidden)
};


UENUM(BlueprintType)
enum class EOptionsListDataModifyReason : uint8
{
    DirectlyModified,
    DependencyModified,
    ResetToDefault
};