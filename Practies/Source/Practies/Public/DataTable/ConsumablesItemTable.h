// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "Engine/DataTable.h"
#include "ConsumablesItemTable.generated.h"

USTRUCT(BlueprintType)
struct FConsumablesDataTable : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConsumType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Texture;

};