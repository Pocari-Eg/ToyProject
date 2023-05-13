// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TOY_LOG, Log, All);
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_W() UE_LOG(TOY_LOG, Warning, TEXT("%s"), *LOG_CALLINFO) // warning Log 
#define LOG_E() UE_LOG(TOY_LOG, Error, TEXT("%s"), *LOG_CALLINFO)// Error Log

#define TLOG_W(Format, ...) UE_LOG(TOY_LOG, Warning, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))//TEXT Warning Log
#define TLOG_E(Format, ...) UE_LOG(TOY_LOG, Error, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))//TEXT Error Log

#define CHECK(Expr, ...) {if(!(Expr)) {BBLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}


UENUM(BlueprintType)
enum class EPState : uint8
{
    idle UMETA(DisplayName = "IDLE"),
    walk UMETA(DisplayName = "WALK"),
    attack UMETA(DisplayName = "ATTACK"),
    skill UMETA(DisplayName = "SKILL"),
};
