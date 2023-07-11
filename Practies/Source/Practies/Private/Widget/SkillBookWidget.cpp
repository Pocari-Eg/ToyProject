// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillBookWidget.h"
#include "PRGameInstance.h"
FSkillType USkillBookWidget::GetSkillType(int SkillCode)
{
	
	auto Instance = Cast<UPRGameInstance>(GetGameInstance());
	auto SkillData = Instance->GetSKillTypeData(SkillCode);

	FSkillType NewSkill;
	NewSkill.Name = SkillData->SkillName;
	FString TextruePath = SkillData->TexturePath;
	NewSkill.Texture= LoadObject<UTexture2D>(NULL, *TextruePath, NULL, LOAD_None, NULL);

	FString MongtagePath = SkillData->MontagePath;
	NewSkill.Montage = LoadObject<UAnimMontage>(NULL, *MongtagePath, NULL, LOAD_None, NULL);

	return NewSkill;
}
