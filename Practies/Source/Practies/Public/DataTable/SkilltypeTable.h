// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkilltypeTable.generated.h"

USTRUCT(BlueprintType)
struct FSkillTypeTable : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TexturePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MontagePath;

};