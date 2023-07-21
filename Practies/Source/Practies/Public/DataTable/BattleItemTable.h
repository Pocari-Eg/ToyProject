// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "Engine/DataTable.h"
#include "BattleItemTable.generated.h"

USTRUCT(BlueprintType)
struct FBattleItemDataTable : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBattleType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Texture;

};