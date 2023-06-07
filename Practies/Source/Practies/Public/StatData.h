// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatData.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FStatData
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
    int HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int ATK;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int MoveSpeed;

};
