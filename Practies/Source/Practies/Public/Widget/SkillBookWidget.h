// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/Skill.h"
#include "SkillBookWidget.generated.h"

/**
 * 
 */


UCLASS()
class PRACTIES_API USkillBookWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
	UFUNCTION(BluePrintCallable)
	FSkillType GetSkillType(int SkillCode);
};
