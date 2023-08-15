// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practies.h"
#include "Engine/Texture2D.h"
#include "ItemData.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FBattleItemData
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBattleItemType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
};

USTRUCT(Atomic, BluePrintType)
struct FRecoveryItemData
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;
};

USTRUCT(Atomic, BluePrintType)
struct FOffenseItemData
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Distance;
};

USTRUCT(Atomic, BluePrintType)
struct FItemTileData
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Code;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBattleTile;

};
USTRUCT(Atomic, BluePrintType)
struct FItemUseState
{
	GENERATED_BODY()

	float MaxCool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurCool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEnabled;

};
