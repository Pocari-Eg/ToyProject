// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "Engine/Texture2D.h"
#include "Item.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FConsumablesItem
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConsumType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;


};