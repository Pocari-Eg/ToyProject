// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Animation/AnimMontage.h"
#include "Skill.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FSkillType
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;
};
struct FSkillDetail
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Angle;
};
USTRUCT(Atomic, BluePrintType)
struct FSkill
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillType SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillLevel;

};