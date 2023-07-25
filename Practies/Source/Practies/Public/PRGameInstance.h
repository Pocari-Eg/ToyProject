// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/Skill.h"
#include "DataTable/SkilltypeTable.h"
#include "Common/Item.h"

#include "DataTable/BattleItemTable.h"
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

	 UDataTable* BattleItemData;
	 UDataTable* RecoveryItemData;
	 UDataTable* OffenseItemData;

	 TArray<int> SkillLevels;
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
	void SetPlayerUseSkill(int idx, int SkillCode);
	UFUNCTION(Blueprintcallable)
	void ErasePlayerSkill(int idx);

	//skilldata
	FSkillTable* GetSKillTypeData(int SkillCode);
	FSkillDetail GetSkillDetailData(FName SkillName, int SkillCode);



	//skill 
	UFUNCTION(BluePrintCallable)
	FSkill GetSkill(int SkillCode);
	UFUNCTION(Blueprintcallable)
	int GetSkillLevel(int SkillCode);
	UFUNCTION(Blueprintcallable)
	void SetSkillLevel(int SkillCode,int Value);
	UFUNCTION(Blueprintcallable)
	UTexture2D* GetSkillImage(FSkill Skill) {return Skill.Texture; }


	//item

	UFUNCTION(Blueprintcallable)
	void SetBattleItem(int idx, int ItemCode);
	UFUNCTION(Blueprintcallable)
	void EraseBattleItem(int idx);

	//Itemldata
	FBattleItemDataTable* GetBattleItemData(int ItemCode);
	FRecoveryItemDataTable* GetRecoveryItemData(FName ItemName);
	FOffenseItemDataTable* GetOffenseItemData(FName ItemName);
	

	UFUNCTION(BluePrintCallable)
	FBattleItem GetBattleItem(int ItemCode);
	UFUNCTION(BluePrintCallable)
	FRecoveryItem GetRecoveryItem(FName ItemName);
	UFUNCTION(BluePrintCallable)
	FOffenseItem GetOffenseItem(FName ItemName);


	UFUNCTION(Blueprintcallable)
	UTexture2D* GetItemImage(FBattleItem Item) { return Item.Texture; }
};
