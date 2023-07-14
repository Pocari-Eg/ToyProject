// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/Skill.h"
#include "DataTable/SkillDetailTable.h"
#include "DataTable/SkilltypeTable.h"
#include "PRGameInstance.generated.h"

/**
 * 
 */
class APlayerCharacter;
UCLASS()
class PRACTIES_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	 APlayerCharacter* Player;
	 UDataTable* SkillTypeData;

	 UDataTable* SkillDetailData;
public:
	UPRGameInstance();
	void BindMonster2PlayerWidget(class AMonster* NewMonster);
	void UnBindMonster2PlayerWidget();

//Get SEt
public:
	void BindPlayer(APlayerCharacter* NewPlayer);
	APlayerCharacter* GetPlayer();

	UFUNCTION(Blueprintcallable)
	void SetMouseOnWidget(bool Value);
	UFUNCTION(Blueprintcallable)
	void SetPlayerUseSkill(int idx, FSkill Data);
	UFUNCTION(Blueprintcallable)
	void ErasePlayerSkill(int idx);

	//skilldata
	FSkillTypeTable* GetSKillTypeData(int SkillCode);

	FSkillDetail GetSkillDetailData(FName SkillName, int SkillLevel);

	UFUNCTION(Blueprintcallable)
	UTexture2D* GetSkillImage(FSkillType SkillType) {return SkillType.Texture; }

};
