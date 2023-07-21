// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Animation/AnimMontage.h"
#include "Skill.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FSkill
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurSkillLevel;

};
USTRUCT(Atomic, BluePrintType)
struct FSkillDetail
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Angle;
	  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	   float CoolTime;
};
USTRUCT(Atomic, BluePrintType)
struct FUseState
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurCool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEnabled;

};
